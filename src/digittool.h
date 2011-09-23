/***************************************************************************
                          digittool.h  -  description
                             -------------------
    begin                : Tue Nov 5 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: digittool.h,v $
    Revision 1.4  2006/12/26 09:03:09  markmitch
    Control click and drag in select mode

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.17  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.15  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.14  2004/01/13 18:53:33  markmitch
    Point match works but needs bells and whistles

    Revision 1.13  2004/01/06 08:14:39  markmitch
    Point match mode highlights sample point

    Revision 1.12  2004/01/01 22:15:04  markmitch
    Delete key deletes. No no-op Cancel buttons. No crash from Divider click

    Revision 1.11  2003/12/29 06:55:10  markmitch
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

#ifndef DIGITTOOL_H
#define DIGITTOOL_H

#include <qobject.h>
#include <q3canvas.h>
#include <qpoint.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <QMouseEvent>
#include <QKeyEvent>

#include "digitdef.h"

class DigitView;
class Point;
class Segment;

// base class handler for keyboard and mouse input 
class DigitTool
{
  public: 

    DigitTool(DigitizeState state);
    virtual ~DigitTool();

    // each tool object corresponds to a particular state
    DigitizeState state(void) { return m_state; }
    
    // methods and members that access the tool appropriate for the current mode
    static DigitTool* findTool(DigitizeState state);
    static Q3PtrList<DigitTool> toolList;

    // area select selects all objects in a rectangular area
    static bool areaSelect;
    
    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e) = 0;
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e) = 0;
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e) = 0;
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e) = 0;
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e) = 0;
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e) = 0;

  protected:

    // edit the graph coordinates of an axis or scale bar point
    bool editAxisPoint(DigitView* view, double* x, double* y);
    bool editScalePoint(DigitView* view, double* length);
    
  private:

    DigitizeState m_state;
};
    
// handler for keyboard and mouse input while in axis mode
class PointAxisTool : public DigitTool
{
  public:

    PointAxisTool();
    ~PointAxisTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);
};

// handler for keyboard and mouse input while in curve mode
class PointCurveTool : public DigitTool
{
  public:

    PointCurveTool();
    ~PointCurveTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);
};

// handler for keyboard and mouse input while in point match mode
class PointMatchTool : public DigitTool
{
  public:

    PointMatchTool();
    ~PointMatchTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);
};

// handler for keyboard and mouse input while in measure mode
class PointMeasureTool : public DigitTool
{
  public:

    PointMeasureTool();
    ~PointMeasureTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);
};

// handler for keyboard and mouse input while in scale bar mode
class ScaleTool : public DigitTool
{
  public:

    ScaleTool();
    ~ScaleTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);

  private:

    // true from mouse press to mouse release
    bool drawingBar;

    // keep track of where cursor was when mouse was pressed
    QPoint cursorDown;
    
    // start and end points
    Point* pointStart;
    Point* pointEnd;
};

// handler for keyboard and mouse input while in segment fill mode
class SegmentTool : public DigitTool
{
  public:

    SegmentTool();
    ~SegmentTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);
    
  private:

    // activate a segment if cursor is over it
    void activateSegment(DigitView* view, QMouseEvent* e);
    
    Segment* activeSegment;
};

// handler for keyboard and mouse input while in select mode
class SelectTool : public DigitTool
{
  public:

    SelectTool();
    ~SelectTool();

    virtual void contentsMouseDoubleClickEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseMoveEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMousePressEvent(DigitView* view, QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(DigitView* view, QMouseEvent* e);
    virtual void keyPressEvent(DigitView* view, QKeyEvent* e);
    virtual void keyReleaseEvent(DigitView* view, QKeyEvent* e);
    
  private:
    
    enum SelectMode
    {
      None,
      Move,
      AreaSelect
    };

    SelectMode selectMode;

    // keep track of where cursor was when mouse was pressed, and at previous refresh
    QPoint cursorDown;
    QPoint cursorLast;
};

#endif // DIGITTOOL_H
