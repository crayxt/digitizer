/***************************************************************************
                          pointset.cpp  -  description
                             -------------------
    begin                : Wed Oct 30 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: pointset.cpp,v $
    Revision 1.6  2006/10/08 06:41:50  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.1  2006/06/09 05:51:44  markmitch
    Fix serialize for 64 bits

    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.29  2004/11/18 05:40:46  markmitch
    Adjust precision of exported results to show significant digits

    Revision 1.28  2004/11/17 08:36:31  markmitch
    Missing export layout buttons were unearthed

    Revision 1.27  2004/11/16 07:59:23  markmitch
    Fix export of x axis log scale

    Revision 1.26  2004/11/09 06:48:07  markmitch
    Prevent unnecessary grid updates

    Revision 1.25  2004/10/07 07:55:48  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.24  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.22  2004/09/24 07:47:58  markmitch
    Bug 102042

    Revision 1.21  2004/09/24 07:05:13  markmitch
    Invisible lines appeared when view selection changed

    Revision 1.20  2004/09/22 06:40:43  markmitch
    Two blanks for gnuplot

    Revision 1.19  2004/09/13 08:32:32  markmitch
    Table-based geometry windows

    Revision 1.18  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.17  2004/09/11 05:59:18  markmitch
    First phase of settings archival

    Revision 1.16  2004/08/12 14:22:44  markmitch
    Blank record between data blocks for gnuplot

    Revision 1.15  2004/08/11 04:51:23  markmitch
    Fix log scale on horizontal axis

    Revision 1.14  2004/04/05 05:39:53  markmitch
    Remove Valgrind warning messages

    Revision 1.13  2004/01/31 18:32:25  markmitch
    Hide lines as well as points

    Revision 1.12  2004/01/29 07:02:22  markmitch
    Line up curve geometry window columns

    Revision 1.11  2004/01/13 17:54:06  markmitch
    Testing point match

    Revision 1.10  2003/12/29 06:55:10  markmitch
    Cvs log cleanup. Color chooser


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <q3canvas.h>
#include <qregexp.h>
#include <q3table.h>
#include <qbitmap.h>
//Added by qt3to4:
#include <Q3PointArray>
#include <QList>
#include <QPixmap>

#include <math.h>

#include "pointset.h"
#include "digitdef.h"
#include "transform.h"
#include "digitdebug.h"
#include "main.h"
#include "defaultsettings.h"
#include "geometrywindowitem.h"

const double PI = 3.1415926535;

PointSet::PointSet() :
  m_export(true),
  m_modifiedGeometry(true)
{
  // the pointset style is set by setStyle

  DigitDebug::ctor(QString("pointset ") + QString::number((ulong) this, 16));
}

PointSet::~PointSet()
{
  DigitDebug::dtor(QString("pointset ") + QString::number((ulong) this, 16));
  
  // cannot delete the points in m_points and lines in m_lines here since they are temporarily
  // shared by multiple pointsets. instead, deleteShared is called just before destruction
}

void PointSet::setVisible(bool visible)
{
  if (visible)
    show();
  else
    hide();
}

void PointSet::deleteShared()
{
  m_lines.setAutoDelete(true);
  m_lines.clear(); // autoDelete is on
  m_lines.setAutoDelete(false);
  
  m_points.setAutoDelete(true);
  m_points.clear(); // autoDelete is on
  m_points.setAutoDelete(false);
}

void PointSet::setStyle(PointSetStyle style)
{
  m_style = style;

  Q3PtrListIterator<Q3CanvasLine> itr(m_lines);
  Q3CanvasLine* line;
  while ((line = itr.current()) != 0)
  {
    ASSERT_ENGAUGE(line != 0);
    line->setPen(PointSetStyles::instance().pointSetPen(m_style.lineColor, m_style.lineSize));

    if (m_style.lineColor == DigitTransparent)
      line->hide();
    else
      line->show();
      
    ++itr;
  }
}
 
void PointSet::addPoint(Q3Canvas* canvas, Point* point, QList<QRect>* updateRectList)
{
  // insert point between two other points if it lies on the line between the two points
  const int LineEpsilonPixels = 2;
  int index = 0;
  ASSERT_ENGAUGE(point != 0);
  double x = point->xScreen();
  double y = point->yScreen();
  Point* pOld = 0;
  for (Point* pNew = m_points.first(); pNew; pNew = m_points.next(), index++)
  {
    ASSERT_ENGAUGE(pNew != 0);
    double xNew = pNew->xScreen();
    double yNew = pNew->yScreen();

    if (pOld)
    {
      double xOld = pOld->xScreen();
      double yOld = pOld->yScreen();

      double xProj, yProj;
      projectpointontoline(x, y, xOld, yOld, xNew, yNew, &xProj, &yProj);

      double diff = sqrt((x - xProj) * (x - xProj) + (y - yProj) * (y - yProj));
      if (diff < LineEpsilonPixels)
      {
        m_points.insert(index, point);
        point->setPointSet(this);

        removeLine(pOld, pNew, updateRectList);
        addLine(canvas, pOld, point, updateRectList);
        addLine(canvas, point, pNew, updateRectList);

        m_modifiedGeometry = true;

        return;
      }
    }

    pOld = pNew;
  }

  // just append point to end of pointset
  m_points.append(point);
  point->setPointSet(this);

  if (pOld)
    addLine(canvas, pOld, point, updateRectList);

  m_modifiedGeometry = true;
}

void PointSet::addLine(Q3Canvas* canvas, Point* pFrom, Point* pTo, QList<QRect>* updateRectList)
{
  ASSERT_ENGAUGE(pFrom);
  ASSERT_ENGAUGE(pTo);

  Q3CanvasLine* line = new Q3CanvasLine(canvas);
  CHECK_PTR_ENGAUGE(line);

  line->setPoints(pFrom->xScreen(), pFrom->yScreen(), pTo->xScreen(), pTo->yScreen());

  line->setPen(PointSetStyles::instance().pointSetPen(m_style.lineColor, m_style.lineSize));
  line->setZ(ZLines);
  if (m_style.lineColor == DigitTransparent)
    line->hide();
  else
    line->show();

  m_lines.append(line);

  pFrom->setLineNext(line);
  pTo->setLinePrev(line);

  QRect rect(
    QPoint(pFrom->xScreen(), pFrom->yScreen()),
    QPoint(pTo->xScreen(), pTo->yScreen()));

  updateRectList->append(rect.normalize());

  m_modifiedGeometry = true;
}

void PointSet::removePoint(Point* p, QList<QRect>* updateRectList)
{
  // remove one of its attached lines. four cases are:
  //   1. solitary point (0 lines->0 lines)
  //   2. leftmost point (1 attached lines->0 attached lines)
  //   3. doubly attached point (2 attached lines->1 attached line)
  //   4. rightmost point (1 attached line->0 attached lines)
  ASSERT_ENGAUGE(p);
  Point* pFirst = m_points.first();
  Point* pLast = m_points.last();
  if (m_points.count() > 1)
  {
    // not case 1
    if ((p == m_points.first()) || (p == m_points.last()))
    {
      Point* pOld = 0;
      for (Point* pNew = m_points.first(); pNew; pNew = m_points.next())
      {
        if (((p == pOld) && (p == pFirst)) ||
          ((p == pNew) && (p == pLast)))
        {
          // cases 2 and 4
          removeLine(pOld, pNew, updateRectList);
          break;
        }

        pOld = pNew;
      }
    }
    else
    {
      Point* pOlder = 0;
      Point* pOld = 0;
      for (Point* pNew = m_points.first(); pNew; pNew = m_points.next())
      {
        if (p == pOld)
        {
          if (pOlder)
          {
            // case 3
            ASSERT_ENGAUGE(updateRectList != 0);
            updateRectList->append(pOlder->lineNext()->boundingRect());

            removeLine(pOld, pNew, updateRectList);

            ASSERT_ENGAUGE(pOlder != 0);
            pOlder->lineNext()->setPoints(
              pOlder->xScreen(), pOlder->yScreen(),
              pNew->xScreen(), pNew->yScreen());
            ASSERT_ENGAUGE(pNew != 0);
            pNew->setLinePrev(pOlder->lineNext());

            updateRectList->append(pOlder->lineNext()->boundingRect());
            break;
          }
        }

        pOlder = pOld;
        pOld = pNew;
      }
    }
  }

  // remove the point, using removeRef (which ignores compareItems) rather than
  // remove (which uses compareItems)
  ASSERT_ENGAUGE(updateRectList != 0);
  updateRectList->append(p->boundingRect());
  if (!m_points.removeRef(p))
  {
    FATAL_ENGAUGE("unable to remove point");
  }
  delete p;

  m_modifiedGeometry = true;
}

void PointSet::removePoints()
{
  QList<QRect> updateRectList;

  Point* p;
  Point* pNext;
  for (p = m_points.first(); p; p = pNext)
  {
    pNext = m_points.next();
    removePoint(p, &updateRectList);
  }

  m_modifiedGeometry = true;
}

void PointSet::removeLine(Point* pFrom, Point* pTo, QList<QRect>* updateRectList)
{
  // consistency checks
  ASSERT_ENGAUGE(pFrom);
  ASSERT_ENGAUGE(pTo);
  ASSERT_ENGAUGE(pFrom->lineNext());
  ASSERT_ENGAUGE(pTo->linePrev());
  ASSERT_ENGAUGE(pFrom->lineNext() == pTo->linePrev());

  if (!m_lines.remove(m_lines.find(pFrom->lineNext())))
  {
    FATAL_ENGAUGE("unable to remove line");
  }

  delete pFrom->lineNext();

  pFrom->setLineNext(0);
  pTo->setLinePrev(0);

  QRect rect(
    QPoint(pFrom->xScreen(), pFrom->yScreen()),
    QPoint(pTo->xScreen(), pTo->yScreen()));

  updateRectList->append(rect.normalize());

  m_modifiedGeometry = true;
}

const PointList* PointSet::points() const
{
  return &m_points;
}

int PointSet::pointCount()
{
  return m_points.count();
}

void PointSet::show()
{
  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(point != 0);
    point->show();
  }

  Q3PtrListIterator<Q3CanvasLine> itr(m_lines);
  Q3CanvasLine* line;
  while ((line = itr.current()) != 0)
  {
    ASSERT_ENGAUGE(line != 0);
    if (m_style.lineColor == DigitTransparent)
      line->hide();
    else
      line->show();

    ++itr;
  }
}

void PointSet::hide()
{
  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(point != 0);
    point->hide();
  }
  
  Q3PtrListIterator<Q3CanvasLine> itr(m_lines);
  Q3CanvasLine* line;
  while ((line = itr.current()) != 0)
  {
    ASSERT_ENGAUGE(line != 0);
    line->hide();

    ++itr;
  }
}

void PointSet::dump()
{
  qDebug("pointset %lx name %s points %d shape %d size %d size %d "
    "color %d color %d size %d color %d connect %d",
    (unsigned long) this, m_name.latin1(), m_points.count(), (int) m_style.pointShape,
    (int) m_style.pointSize, (int) m_style.pointLineSize,
    (int) m_style.pointLineColor, (int) m_style.pointInColor,
    (int) m_style.lineSize, (int) m_style.lineColor,
    (int) m_style.lineConnectAs);

  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(point != 0);
    point->dumpPoint();
  }

  Q3PtrListIterator<Q3CanvasLine> itr(m_lines);
  Q3CanvasLine* line;
  while ((line = itr.current()) != 0)
  {
    ASSERT_ENGAUGE(line != 0);
    qDebug("pointset line %lx pointset %lx start (%d, %d) end (%d, %d)",
      (unsigned long) line, (unsigned long) this,
      line->startPoint().x(), line->startPoint().y(),
      line->endPoint().x(), line->endPoint().y());

    ++itr;
  }
}

void PointSet::attachPointsToPointSet()
{
  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(point != 0);
    point->setPointSet(this);
  }

  m_modifiedGeometry = true;
}

void PointSet::updateGraphCoordinates(CoordSettings coord, const Transform* transform)
{
  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    double xTheta, yR;
    ASSERT_ENGAUGE(transform != 0);
    ASSERT_ENGAUGE(point != 0);
    transform->screenToXThetaYR(coord, point->xScreen(), point->yScreen(), &xTheta, &yR);

    point->setXThetaGraph(xTheta);
    point->setYRGraph(yR);
  }

  m_modifiedGeometry = true;
}

bool PointSet::singleValued(CoordSettings coord, const Transform* transform)
{
  bool first = true;
  double xThetaLast = 0.0, xTheta, yR;
  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(transform != 0);
    ASSERT_ENGAUGE(point != 0);
    transform->screenToXThetaYR(coord, point->xScreen(), point->yScreen(), &xTheta, &yR);

    if (!first && (xTheta < xThetaLast))
      return false;

    xThetaLast = xTheta;
    first = false;
  }

  return true;
}

void PointSet::forceSingleValued(CoordSettings coord, const Transform* transform,
  QList<QRect>* updateRectList)
{ 
  // quick exit if pointset is a closed contour, which is the case for all axis, scale and
  // measure pointsets. curve pointsets may be either single valued functions, or closed contours
  if (m_style.lineConnectAs != SingleValuedFunction)
    return;

  // quick exit if points are already in order
  if (singleValued(coord, transform))
    return;

  // sort the points by xTheta
  m_points.sort();

  // to prevent having to remove N lines and then immediately adding N lines, we only
  // adjust as many lines as necessary
  Point* pOlder = 0;
  Point* pOld = m_points.last();
  for (Point* pNew = m_points.first(); pNew; pNew = m_points.next())
  {
    if (pOlder)
    {
      // second condition handles when last point is moved to before first point
      if ((pOlder->lineNext() != pNew->linePrev()) || (pNew->linePrev() == 0))
      {
        if (!pOlder->lineNext())
        {
          // previous point was originally at the end of the list so it has
          // no next line. use the next line of the point now at the end
          pOlder->setLineNext(pOld->lineNext());

          pOld->setLineNext(0);
        }

        updateRectList->append(pOlder->lineNext()->boundingRect());

        pOlder->lineNext()->setPoints(
          pOlder->xScreen(), pOlder->yScreen(),
          pNew->xScreen(), pNew->yScreen());

        updateRectList->append(pOlder->lineNext()->boundingRect());

        pNew->setLinePrev(pOlder->lineNext());
      }
    }
    else
    {
      // this is the first point. make sure it has no previous line
      pNew->setLinePrev(0);
    }

    pOlder = pNew;
  }

  m_modifiedGeometry = true;
}

bool PointSet::pointSetGraphLimits(double *xThetaMin, double *xThetaMax, double *yRMin, double *yRMax)
{
  ASSERT_ENGAUGE(xThetaMin != 0);
  ASSERT_ENGAUGE(xThetaMax != 0);
  ASSERT_ENGAUGE(yRMin != 0);
  ASSERT_ENGAUGE(yRMax != 0);
  
  bool found = false;

  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(point != 0);
    if (!found || (point->xThetaGraph() < *xThetaMin))
      *xThetaMin = point->xThetaGraph();
    if (!found || (point->xThetaGraph() > *xThetaMax))
      *xThetaMax = point->xThetaGraph();
    if (!found || (point->yRGraph() < *yRMin))
      *yRMin = point->yRGraph();
    if (!found || (point->yRGraph() > *yRMax))
      *yRMax = point->yRGraph();

    found = true;
  }

  return found;
}

bool PointSet::pointSetScreenLimits(double *xMin, double *xMax, double *yMin, double *yMax)
{
  ASSERT_ENGAUGE(xMin != 0);
  ASSERT_ENGAUGE(xMax != 0);
  ASSERT_ENGAUGE(yMin != 0);
  ASSERT_ENGAUGE(yMax != 0);

  bool found = false;

  for (Point* point = m_points.first(); point; point = m_points.next())
  {
    ASSERT_ENGAUGE(point != 0);
    if (!found || (point->xScreen() < *xMin))
      *xMin = point->xScreen();
    if (!found || (point->xScreen() > *xMax))
      *xMax = point->xScreen();
    if (!found || (point->yScreen() < *yMin))
      *yMin = point->yScreen();
    if (!found || (point->yScreen() > *yMax))
      *yMax = point->yScreen();

    found = true;
  }

  return found;
}

void PointSet::mergeUniqueXValues(QList<double>* list,
  int xPrecision)
{
  ASSERT_ENGAUGE(list != 0);
  
  Point* p = m_points.first();
  QList<double>::iterator itr;
 
  // insert member points that should go before any points already in the list
  for (itr = list->begin(); p && (itr != list->end()); ++itr)
    for (; p && (p->xThetaGraph() < (*itr)); p = m_points.next())
      list->insert(itr, p->xThetaGraph());

  // insert member points that should go after all points already in the list
  for (; p; p = m_points.next())
    list->append(p->xThetaGraph());

  // remove duplicate entries caused by two or more curves having points with identical
  // exported x coordinates, since these duplicates are useless and cause problems (i.e. sql
  // insert will crash)
  QString xLast, xNew;
  for (itr = list->begin(); itr != list->end(); ++itr)
  {
    xNew.setNum(*itr, 'g', xPrecision);
    
    if (xLast == xNew)
      itr = list->remove(itr);

    xLast = xNew;
  }
}

QString PointSet::exportCurveAll(ExportSettings xport, int xPrecision, int yPrecision)
{
  QString rtn;
  
  // if this curve is a function, then skip points whose exported x value is the same
  // as the previous point so the output can be imported into any sql database that
  // requires unique x values
  QString xLast, xNew, yNew;

  for (Point* p = m_points.first(); p; p = m_points.next())
  {
    xNew.setNum(p->xThetaGraph(), 'g', xPrecision);
    yNew.setNum(p->yRGraph(), 'g', yPrecision);
    
    if ((xLast != xNew) ||
      (m_style.lineConnectAs != SingleValuedFunction))
    {
      rtn += xNew;
      rtn += delimiter(xport.delimiters);
      rtn += yNew;
      rtn += "\n";
    }

    xLast = xNew;
  }

  return rtn;
}

QString PointSet::exportCurveHeader(ExportSettings xport)
{
  QString filtered(m_name);
  filtered.replace(QRegExp(delimiter(xport.delimiters)), QString(""));

  return filtered;
}

QString PointSet::exportCurvePoint(double x, CoordSettings coord, bool useInterpolation,
  int yPrecision)
{
  QString yNew; // initial empty value might be returned if interpolation is disabled
  
  if (m_points.count() == 0)
    return yNew;
    
  if (!useInterpolation)
  {
    // x value has to exactly match one of the points in this curve
    PointListIterator itr(m_points);
    Point* p;
    while ((p = itr.current()) != 0)
    {
      if (x == p->xThetaGraph())
        return yNew.setNum(p->yRGraph(), 'g', yPrecision);
      ++itr;
    }

    return yNew;
  }

  if (m_points.count() == 1)
    return yNew.setNum(m_points.first()->yRGraph(), 'g', yPrecision);
    
  // this sequential search suffers from n-squared performance, since saving
  // the two iterators as member variables between invocations caused problems
  // when deleting and copying pointsets
  PointListIterator* m_itrLeft = new PointListIterator(m_points);
  CHECK_PTR_ENGAUGE(m_itrLeft);
  PointListIterator* m_itrRight = new PointListIterator(m_points);
  CHECK_PTR_ENGAUGE(m_itrRight);
  ++(*m_itrRight);

  // loop until x value is between the left and right points, or we reach the end of the list
  while ((x > m_itrRight->current()->xThetaGraph()) && !m_itrRight->atLast())
  {
    ++(*m_itrLeft);
    ++(*m_itrRight);
  }

  Point* pLeft = m_itrLeft->current();
  Point* pRight = m_itrRight->current();

  ASSERT_ENGAUGE(pLeft != 0);
  ASSERT_ENGAUGE(pRight != 0);
  double leftPointX = pLeft->xThetaGraph();
  double rightPointX = pRight->xThetaGraph();
  double leftPointY = pLeft->yRGraph();
  double rightPointY = pRight->yRGraph();
  if (adjustForLogScale(coord.xThetaScale, &leftPointX) &&
    adjustForLogScale(coord.xThetaScale, &rightPointX) &&
    adjustForLogScale(coord.xThetaScale, &x) &&
    adjustForLogScale(coord.yRScale, &leftPointY) &&
    adjustForLogScale(coord.yRScale, &rightPointY))
  { 
    double denominator = rightPointX - leftPointX;
    if (denominator < DefaultSettings::instance().getDoubleMin())
      yNew.setNum(leftPointX, 'g', yPrecision);
    else
    {
      // if x value is between the points this is an interpolation (0<s<1), otherwise an extrapolation
      double s = (x - leftPointX) / denominator;

      // interpolate or extrapolate
      double otherPoint = (1.0 - s) * leftPointY + s * rightPointY;

      // adjust for log scale
      if (coord.yRScale == Log)
        otherPoint = pow((double) 10.0, otherPoint);
        
      yNew.setNum(otherPoint, 'g', yPrecision);
    }
  }

  return yNew;
}

bool PointSet::adjustForLogScale(Scale scale, double* pointXY)
{
  ASSERT_ENGAUGE(pointXY != 0);
  
  if (scale == Log)
  {
    if (*pointXY <= 0.0)
      return false;
      
    *pointXY = log10(*pointXY);
  }

  return true;
}

void PointSet::serializeWrite(QDataStream &s) const
{
  s << m_name;
  s << (Q_INT32 &) m_style.pointShape;
  s << (Q_INT32 &) m_style.pointSize;
  s << (Q_INT32 &) m_style.pointLineSize;
  s << (Q_INT32 &) m_style.pointLineColor;
  s << (Q_INT32 &) m_style.pointInColor;
  s << (Q_INT32 &) m_style.lineSize;
  s << (Q_INT32 &) m_style.lineColor;
  s << (Q_INT32 &) m_style.lineConnectAs;

  s << (const Q_INT32 &) m_points.count();
  PointListIterator itr(m_points);
  Point* point;
  while ((point = itr.current()) != 0)
  {
    s << point->xScreen();
    s << point->yScreen();
    s << point->xThetaGraph();
    s << point->yRGraph();
    ++itr;
  }
}

void PointSet::serializeRead(QDataStream &s, Q3Canvas* canvas)
{
  ASSERT_ENGAUGE(canvas != 0);
  
  s >> m_name;
  s >> (Q_INT32 &) m_style.pointShape;
  s >> (Q_INT32 &) m_style.pointSize;
  s >> (Q_INT32 &) m_style.pointLineSize;
  s >> (Q_INT32 &) m_style.pointLineColor;
  s >> (Q_INT32 &) m_style.pointInColor;
  s >> (Q_INT32 &) m_style.lineSize;
  s >> (Q_INT32 &) m_style.lineColor;
  s >> (Q_INT32 &) m_style.lineConnectAs;

  int count;
  s >> (Q_INT32 &) count;
  QList<QRect> updateRectList;
  for (int i = 0; i < count; i++)
  {
    int xScreen, yScreen;
    double xGraph, yGraph;
    s >> xScreen;
    s >> yScreen;
    s >> xGraph;
    s >> yGraph;
    Point* point = new Point(xScreen, yScreen, xGraph, yGraph, canvas);
    CHECK_PTR_ENGAUGE(point);

    addPoint(canvas, point, &updateRectList);
  }

  m_modifiedGeometry = true;

  // do not call attachPointsToPointSet here since this pointet is temporary for graph pointsets. call
  // attachPointsToPointSet in the function that calls this
}

void PointSet::geometryInfo(bool validTransform, bool cartesian, int* pNextRow,
  GeometryWindowItemList& rInfo)
{
  ASSERT_ENGAUGE(pNextRow != 0);

  // header
  QString s = QObject::tr("Name:");
  rInfo.append(GeometryWindowItem(*pNextRow, 0, s));
  rInfo.append(GeometryWindowItem(*pNextRow, 1, m_name));

  ++(*pNextRow);
  
  rInfo.append(GeometryWindowItem(*pNextRow, 0, QString("Units:")));
  rInfo.append(GeometryWindowItem(*pNextRow, 1, (validTransform ? QObject::tr("Graph") : QObject::tr("Pixels"))));

  ++(*pNextRow);

  geometryInfoArea(pNextRow, rInfo);
  geometryInfoDistance(pNextRow, rInfo, cartesian);

  m_modifiedGeometry = false;
}

void PointSet::geometryInfoArea(int* pNextRow, GeometryWindowItemList& rInfo)
{
  double funcArea = 0.0, polyArea = 0.0;
  int i, nPoints = m_points.count();
  Point* point;

  if (nPoints > 2)
  {
    double* x = new double [nPoints];
    CHECK_PTR_ENGAUGE(x);
    double* y = new double [nPoints];
    CHECK_PTR_ENGAUGE(y);

    for (i = 0, point = m_points.first(); point; point = m_points.next(), i++)
    {
      ASSERT_ENGAUGE(point != 0);
      x [i] = point->xThetaGraph();
      y [i] = point->yRGraph();
    }

    funcArea = functionarea(nPoints, x, y);
    polyArea = polygonarea(nPoints, x, y);

    delete[] x;
    delete[] y;
  }

  ASSERT_ENGAUGE(pNextRow != 0);
  
  rInfo.append(GeometryWindowItem(*pNextRow, 0, QObject::tr("FuncArea")));
  rInfo.append(GeometryWindowItem(*pNextRow, 1, QString::number(funcArea)));

  ++(*pNextRow);

  rInfo.append(GeometryWindowItem(*pNextRow, 0, QObject::tr("PolyArea")));
  rInfo.append(GeometryWindowItem(*pNextRow, 1, QString::number(polyArea)));

  ++(*pNextRow);
}

void PointSet::geometryInfoDistance(int *pNextRow, GeometryWindowItemList& rInfo, bool cartesian)
{
  QString line;
  bool firstPoint;
  double xLast = 0.0, yLast = 0.0, x, y;
  double totalDistance = 0.0, distance;
  int i, pass;
  Point* point;

  ASSERT_ENGAUGE(pNextRow != 0);

  rInfo.append(GeometryWindowItem(*pNextRow, 0, (cartesian ? QObject::tr("X") : QObject::tr("Theta"))));
  rInfo.append(GeometryWindowItem(*pNextRow, 1, (cartesian ? QObject::tr("Y") : QObject::tr("R"))));
  rInfo.append(GeometryWindowItem(*pNextRow, 2, QObject::tr("Index")));
  rInfo.append(GeometryWindowItem(*pNextRow, 3, QObject::tr("Distance")));
  rInfo.append(GeometryWindowItem(*pNextRow, 4, QObject::tr("Percent")));
  rInfo.append(GeometryWindowItem(*pNextRow, 5, QObject::tr("Distance")));
  rInfo.append(GeometryWindowItem(*pNextRow, 6, QObject::tr("Percent")));
  rInfo.append(GeometryWindowItem(*pNextRow, 7, QObject::tr("Angle")));

  ++(*pNextRow);

  // first pass computes totalDistance and xLast and yLast, second pass outputs one line per point
  for (pass = 0; pass < 2; pass++)
  {
    firstPoint = true;
    distance = 0.0;
    PointListIterator itr(m_points), itrNext(m_points);
    ++itrNext;
    for (i = 0; itr.current(); ++itr, ++itrNext, i++)
    {
      point = itr.current();

      x = point->xThetaGraph();
      y = point->yRGraph();

      if (!firstPoint)
        distance += sqrt((x - xLast) * (x - xLast) + (y - yLast) * (y - yLast));

      if (pass == 1)
        geometryInfoDistancePass1(i, itrNext, xLast, yLast, x, y, distance, totalDistance,
          pNextRow, rInfo);

      firstPoint = false;
      xLast = x;
      yLast = y;
    }

    totalDistance = distance;
  }
}

void PointSet::geometryInfoDistancePass1(int i, PointListIterator &itrNext,
  double xLast, double yLast, double x, double y,
  double distance, double totalDistance, int* pNextRow, GeometryWindowItemList& rInfo)
{
  if (!itrNext.current())
    itrNext.toFirst();

  Point* pointNext = itrNext.current();

  ASSERT_ENGAUGE(pointNext != 0);
  double xNext = pointNext->xThetaGraph();
  double yNext = pointNext->yRGraph();

  double pcDistance;
  if (totalDistance <= 0.0)
    pcDistance = 100.0;
  else
    pcDistance = 100.0 * distance / totalDistance;

  double r1[3], r2[3];
  r1[0] = xLast - x; // xLast from last point of pass 0 is used by first point in pass 1
  r1[1] = yLast - y; // yLast from last point of pass 0 is used by first point in pass 1
  r1[2] = 0.0;
  r2[0] = xNext - x;
  r2[1] = yNext - y;
  r2[2] = 0.0;
  double angle = dangle(r1, r2) * 180.0 / PI;

  ASSERT_ENGAUGE(pNextRow != 0);
  
  rInfo.append(GeometryWindowItem(*pNextRow, 0, QString::number(x)));
  rInfo.append(GeometryWindowItem(*pNextRow, 1, QString::number(y)));
  rInfo.append(GeometryWindowItem(*pNextRow, 2, QString::number(i)));
  rInfo.append(GeometryWindowItem(*pNextRow, 3, QString::number(distance)));
  rInfo.append(GeometryWindowItem(*pNextRow, 4, QString::number(pcDistance)));
  rInfo.append(GeometryWindowItem(*pNextRow, 5, QString::number(totalDistance - distance)));
  rInfo.append(GeometryWindowItem(*pNextRow, 6, QString::number(100.0 - pcDistance)));
  rInfo.append(GeometryWindowItem(*pNextRow, 7, QString::number(angle)));

  ++(*pNextRow);
}

Q3PointArray PointSet::pointSetCoordinates()
{
  Q3PointArray points(m_points.count());

  int i = 0;
  for (Point* point = m_points.first(); point; point = m_points.next(), i++)
    points.setPoint(i, point->xScreen(), point->yScreen());

  return points;
}

QPixmap PointSet::thumbnail()
{
  Q3Canvas c(12, 12);
  Point p(6, 6, &c);
  p.setPointSet(this);

  QPixmap pm(12, 12);
  QPainter painter(&pm);
  c.drawArea(c.rect(), &painter);

  // remove pixmap background so background of requesting widget will appear
  pm.setMask(pm.createHeuristicMask());

  return pm;
}
