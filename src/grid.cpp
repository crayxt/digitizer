/***************************************************************************
                          grid.cpp  -  description
                             -------------------
    begin                : Tue Nov 19 2002
    copyright            : (C) 2002 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: grid.cpp,v $
    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.18  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.16  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.15  2004/09/11 05:59:17  markmitch
    First phase of settings archival

    Revision 1.14  2003/12/29 06:55:10  markmitch
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

#include "grid.h"
#include "gridmesh.h"
#include "transform.h"
#include "digitdebug.h"
#include "main.h"
#include "pointsetstyles.h"

Grid::Grid(GridType gridType, Q3Canvas* canvas) :
  m_gridType(gridType),
  m_canvas(canvas),
  m_grid(false)
{
  DigitDebug::ctor(QString("grid ") + QString::number((ulong) this, 16));
  
  m_lines.setAutoDelete(true);
}

Grid::~Grid()
{
  DigitDebug::dtor(QString("grid ") + QString::number((ulong) this, 16));
  
  m_lines.clear(); // autoDelete is on
}

void Grid::makeGridLines(const Transform* transform, const CoordSettings coord,
  const GridMeshSettings grid)
{
  // remove all old grid lines from previous calls
  m_lines.clear(); // autoDelete is on

  GridMesh gridMesh;
  GridlinesScreen gridlines = gridMesh.makeGridLines(transform, coord, grid);
  GridlinesScreen::iterator itr;
  for (itr = gridlines.begin(); itr != gridlines.end(); ++itr)
  {
    Q3CanvasLine* line = new Q3CanvasLine(m_canvas);
    CHECK_PTR_ENGAUGE(line);
    line->setPoints((*itr).start.x(), (*itr).start.y(), (*itr).stop.x(), (*itr).stop.y());
    line->setPen(gridlinePen((*itr).R));
    line->setZ(ZGridLines);

    m_lines.append(line);
  }
}

QPen Grid::gridlinePen(bool R)
{
  // line width other than 1 is not implemented in Qt 2.3
  const int ONLY_AVAILABLE_WIDTH = 1;

  if (m_gridType == GridTypeRemoval)
    return PointSetStyles::instance().pointSetPen(DigitBlack, ONLY_AVAILABLE_WIDTH);
  else
    if (R)
      return PointSetStyles::instance().pointSetPen(DigitBlack, ONLY_AVAILABLE_WIDTH, Qt::DotLine);
    else
      return PointSetStyles::instance().pointSetPen(DigitBlack, ONLY_AVAILABLE_WIDTH, Qt::DashLine);
}

void Grid::showGrid(bool toggle)
{
  m_grid = toggle;

  Q3CanvasLine* line;
  for (line = m_lines.first(); line; line = m_lines.next())
  {
    ASSERT_ENGAUGE(line != 0);
    line->setVisible(toggle);
  }
}
