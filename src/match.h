/***************************************************************************
                          match.h  -  description
                             -------------------
    begin                : Mon Jan 12 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: match.h,v $
    Revision 1.4  2006/12/20 08:20:26  markmitch
    Rework of point matching to handle skipping

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.7  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.5  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.4  2004/01/19 17:56:32  markmitch
    Combobox focus. Point match style. Empty accepted list

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

#ifndef MATCH_H
#define MATCH_H

#include <q3canvas.h>
#include <qrect.h>
//Added by qt3to4:
#include <Q3PointArray>

#include "digitdef.h"
#include "pointsetstyles.h"

// class used to store match points. This class essentially duplicates the
// basic idea of the more important Point class, with irrelevant functionality
// removed and point match functionality added
class Match : public Q3CanvasPolygonalItem
{
  public:

    Match(int xScreen, int yScreen,
      Color colorAccepted, Color colorRejected,
      PointSetStyle style, Q3Canvas* canvas);
    ~Match();

    enum MatchState
    {
      StateAccepted,
      StateRejected,
      StateUnmarked
    };

    // change state
    MatchState state(void) { return m_state; }
    void setState(MatchState state);

    // change point style
    void setPointSetStyle(PointSetStyle style) { m_pointSetStyle = style; }

    // location
    int x(void) { return m_xScreen; }
    int y(void) { return m_yScreen; }
    
    // debug
    void dumpMatch(void);

  protected:
  
    // QCanvasPolygonalItem function that draws the polygonal item using the pen and brush
    void drawShape(QPainter& p);
    
  private:

    // QCanvasPolygonalItem function that returns the bounding points
    virtual Q3PointArray areaPoints(void) const;
     
    // screen coordinates are in pixels. They are only modified by a click-and-drag operation
    int m_xScreen;
    int m_yScreen;
    
    // colors in accepted and rejected states. these override the style
    Color m_colorAccepted;
    Color m_colorRejected;

    // state of this match point
    MatchState m_state;

    // point style
    PointSetStyle m_pointSetStyle;
};

#endif // MATCH_H
