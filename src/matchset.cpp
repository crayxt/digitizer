/***************************************************************************
                          matchset.cpp  -  description
                             -------------------
    begin                : Mon Jan 12 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: matchset.cpp,v $
    Revision 1.7  2006/12/26 09:03:09  markmitch
    Control click and drag in select mode

    Revision 1.6  2006/12/20 08:20:26  markmitch
    Rework of point matching to handle skipping

    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.11  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.9  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.8  2004/09/11 05:59:18  markmitch
    First phase of settings archival

    Revision 1.7  2004/01/20 03:46:33  markmitch
    Empty match list

    Revision 1.6  2004/01/19 18:06:38  markmitch
    White space at end of file

    Revision 1.5  2004/01/19 17:56:32  markmitch
    Combobox focus. Point match style. Empty accepted list

    Revision 1.4  2004/01/15 08:24:48  markmitch
    Delete keypress. Documentation

    Revision 1.3  2004/01/14 06:54:38  markmitch
    Point match works well and has documentation

    Revision 1.2  2004/01/13 18:53:33  markmitch
    Point match works but needs bells and whistles

    Revision 1.1  2004/01/13 17:54:06  markmitch
    Testing point match


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
//Added by qt3to4:
#include <Q3ValueList>

#include "matchset.h"
#include "digitdef.h"
#include "digitdebug.h"
#include "highlight.h"
#include "main.h"
#include "match.h"
#include "defaultsettings.h"

MatchSet::MatchSet() :
  m_canvas(0),
  m_matches(0),
  m_highlightCandidate(0)
{
  DigitDebug::ctor(QString("matchset ") + QString::number((ulong) this, 16));
  
  m_matchList.setAutoDelete(true);
}

MatchSet::~MatchSet()
{
  DigitDebug::dtor(QString("matchset ") + QString::number((ulong) this, 16));
  
  Q3ValueList<QRect> updateRectList;
  clear(&updateRectList);
  
  if (m_highlightCandidate)
    delete m_highlightCandidate;
}

void MatchSet::acceptedPoints(Q3ValueList<QPoint>* acceptedPoints)
{
  Match* m;
  for (m = m_matchList.first(); m != 0; m = m_matchList.next())
  {
    if (m->state() == Match::StateAccepted)
    {
      QPoint p(m->x(), m->y());

      ASSERT_ENGAUGE(acceptedPoints != 0);
      acceptedPoints->append(p);
    }
  }
}

void MatchSet::addCreatedPointsToCanvas(Q3Canvas* canvas, PointSetStyle style,               
  PointMatchSettings settings, const Q3ValueList<PointMatchTriplet>* pointsCreated,
  Q3ValueList<QRect>* updateRectList)
{
  // make sure we have no stale points from previous invocations
  if (m_matchList.count() > 0)
    clear(updateRectList);

  m_canvas = canvas;
  m_settings = settings;
  
  Q3ValueList<PointMatchTriplet>::const_iterator itr;
  for (itr = pointsCreated->begin(); itr != pointsCreated->end(); ++itr)
  {
    PointMatchTriplet t = (*itr);

    Match* m = new Match(t.x, t.y,
      settings.acceptedColor, settings.rejectedColor,
      style, canvas);
    CHECK_PTR_ENGAUGE(m);

    m_matchList.append(m);
  }

  // create the highlight
  m_highlightCandidate = new Highlight(m_settings.candidateColor, canvas);
  CHECK_PTR_ENGAUGE(m_highlightCandidate);

  moveHighlights(updateRectList);
}

void MatchSet::clear(Q3ValueList<QRect>* updateRectList)
{
  if (m_highlightCandidate)
  {
    updateRectList->append(m_highlightCandidate->boundingRect());
    delete m_highlightCandidate;
    m_highlightCandidate = 0;
  }

  while (m_matchList.count() > 0)
  {
    ASSERT_ENGAUGE(updateRectList != 0);
    updateRectList->append(m_matchList.last()->boundingRect());
    
    m_matchList.removeLast(); // autoDelete is on
  }
}

Q3CanvasRectangle* MatchSet::makeHighlight(Color color)
{
  ASSERT_ENGAUGE(m_canvas != 0);
  Q3CanvasRectangle* r = new Q3CanvasRectangle(0, 0,
    DefaultSettings::instance().getPointMatchHighlightDiameter(),
    DefaultSettings::instance().getPointMatchHighlightDiameter(),
    m_canvas);
  CHECK_PTR_ENGAUGE(r);
  r->setPen(PointSetStyles::instance().pointSetPen(color,
    DefaultSettings::instance().getPointMatchHighlightLineSize()));
  r->setVisible(true);

  return r;
}

bool MatchSet::matchPointAccept(Q3ValueList<QRect>* updateRectList)
{
  Match* m;
  for (m = m_matchList.first(); m != 0; m = m_matchList.next())
  {
    if (m->state() == Match::StateUnmarked)
    {
      m->setState(Match::StateAccepted);

      ASSERT_ENGAUGE(updateRectList != 0);
      updateRectList->append(m->boundingRect());

      moveHighlights(updateRectList);
      
      return true;
    }
  }

  return false;
}

bool MatchSet::matchPointReject(Q3ValueList<QRect>* updateRectList)
{
  Match* m;
  for (m = m_matchList.first(); m != 0; m = m_matchList.next())
  {
    if (m->state() == Match::StateUnmarked)
    {
      m->setState(Match::StateRejected);

      ASSERT_ENGAUGE(updateRectList != 0);
      updateRectList->append(m->boundingRect());

      moveHighlights(updateRectList);
      
      return true;
    }
  }

  return false;
}

bool MatchSet::matchPointRemove(Q3ValueList<QRect>* updateRectList)
{
  Match* mLastNotRejected = 0;
  Match* m;
  for (m = m_matchList.first(); m != 0; m = m_matchList.next())
  {
    if (m->state() == Match::StateUnmarked)
    {
      if (mLastNotRejected != 0)
      {
        mLastNotRejected->setState(Match::StateUnmarked);

        ASSERT_ENGAUGE(updateRectList != 0);
        updateRectList->append(m->boundingRect());

        moveHighlights(updateRectList);
        
        return true;
      }
      else
        return false;
    }

    mLastNotRejected = m;
  }

  // all points are accepted, so reject the last point
  m = m_matchList.last();
  if (m != 0)
  {
    m->setState(Match::StateUnmarked);
    ASSERT_ENGAUGE(updateRectList != 0);
    updateRectList->append(m->boundingRect());
  }

  moveHighlights(updateRectList);
  
  return true;
}

void MatchSet::moveHighlights(Q3ValueList<QRect>* updateRectList)
{
  Match* m;
  for (m = m_matchList.first(); m != 0; m = m_matchList.next())
  {
    if (m->state() == Match::StateUnmarked)
    {
      if (m_highlightCandidate == 0)
      {
        ASSERT_ENGAUGE(m_canvas != 0);
        m_highlightCandidate = new Highlight(m_settings.candidateColor, m_canvas);
        CHECK_PTR_ENGAUGE(m_highlightCandidate);
      }
      else
        updateRectList->append(m_highlightCandidate->boundingRect());
      m_highlightCandidate->moveCenter(m->x(),
                                       m->y());

      if (m_highlightCandidate != 0)
        updateRectList->append(m_highlightCandidate->boundingRect());     
      return;
    }
  }

  if (m_highlightCandidate != 0)
  {
    updateRectList->append(m_highlightCandidate->boundingRect());
    delete m_highlightCandidate;
    m_highlightCandidate = 0;
  }
}

void MatchSet::setPointSetStyle(PointSetStyle style)
{
  for (Match* m = m_matchList.first(); m != 0; m = m_matchList.next())
    m->setPointSetStyle(style);
}
