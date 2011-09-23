/***************************************************************************
                          digitview.h  -  description
                             -------------------
    begin                : Tue Oct 29 14:43:44 PST 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: digitview.h,v $
    Revision 1.4  2006/12/26 09:03:09  markmitch
    Control click and drag in select mode

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.22  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.20  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.19  2004/09/09 05:33:45  markmitch
    Invoker in work. Windows upgrade to 3.3.3

    Revision 1.18  2004/01/15 08:24:48  markmitch
    Delete keypress. Documentation

    Revision 1.17  2004/01/13 18:53:33  markmitch
    Point match works but needs bells and whistles

    Revision 1.16  2004/01/06 08:14:39  markmitch
    Point match mode highlights sample point

    Revision 1.15  2003/12/29 06:55:10  markmitch
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

#ifndef DIGITVIEW_H
#define DIGITVIEW_H

#include <q3canvas.h>
#include <qwidget.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <Q3PointArray>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QCloseEvent>

#include "digitdef.h"

class DigitDoc;
class Segment;
class Point;

// display one view of the canvas belonging to the active document
class DigitView : public Q3CanvasView
{
  Q_OBJECT

  friend class DigitDoc;

  public:

    DigitView(DigitDoc* doc, QWidget* parent, const char* name, Qt::WindowFlags wFlags);
    ~DigitView();

    // returns a pointer to the document connected to the view
    DigitDoc* document() const { return m_doc; }
    
    // method to redraw the document contents if it has been modified
    void update(DigitView* sender, QRect boundingRect);

    // show rubber band rectangle around selected area
    void showAreaSelectMove(QPoint cursorDown, QPoint cursorLast, QPoint cursorNext);
    void showAreaSelectEnd(QPoint cursorDown, QPoint cursorLast);
    
    // show rubber band line segment to preview scale bar
    void showScaleBarMove(QPoint cursorDown, QPoint cursorLast, QPoint cursorNext);
    void showScaleBarEnd(QPoint cursorDown, QPoint cursorLast);    

    // return a list of objects in the specified region
    Q3CanvasItemList collisionsFiltered(QPoint p, int rtti);
    Q3CanvasItemList collisionsFiltered(QPoint p1, QPoint p2, int rtti);
    Q3CanvasItemList collisionsFiltered(Q3CanvasItemList listIn, int rtti);
    
    // move everything that is selected. attached lines are moved also 
    void moveSelection(QPoint delta);

    // select and unselect items
    void selectItemsReplace(Q3CanvasItemList* list);
    void selectSegment(Segment* segment);
    void selectItemsToggle(Q3CanvasItemList* list); // select unselected items and unselect selected items
    void unselect(void);

    // return true if point is currently selected
    bool pointIsSelected(Q3CanvasItem* item);

    // return true if anything is currently selected
    bool isSelection(void) { return selectionList.count() > 0; }

    // zoom get. set is performed by slotZoomChange
    int zoom(void) { return m_zoom; }

    // tell all views to add or remove a sample match point
    void addSampleMatchPoint(const Q3PointArray &samplePointPixels);
    void removeSampleMatchPoint(void);

  public slots:

    void slotZoomChange(const QString &zoom);

  protected:

    // event handlers
    virtual void closeEvent(QCloseEvent* e);
    virtual void contentsMouseDoubleClickEvent(QMouseEvent* e);
    virtual void contentsMouseMoveEvent(QMouseEvent* e);
    virtual void contentsMousePressEvent(QMouseEvent* e);
    virtual void contentsMouseReleaseEvent(QMouseEvent* e);
    virtual void keyPressEvent(QKeyEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);

  private:

    DigitDoc* m_doc;
    
    // draw rubber band rectangle (around selection area) or line segment (to show future scale bar),
    // described by two points. the rubber band appears as a set of inverted pixels. external
    // code is responsible for calling this an even number of times
    void drawRubberBandRectangle(QPoint corner1, QPoint corner2);
    void drawRubberBandLine(QPoint start, QPoint end);

    // items selected in this view
    Q3PtrList<Q3CanvasItem> m_selectedItems;

    // selection list
    Q3CanvasItemList selectionList;

    // only Points can be selected and moved. verify this before making an upcast, returning
    // zero if canvas item is not a point
    Point* safeUpcast(Q3CanvasItemList::iterator itr);

    // handles around the select items or sample match point. there are either 0 or 8 items in this list
    Q3PtrList<Q3CanvasRectangle> m_handles;

    // add handles around selectionList and remove current handles
    void addHandles(const QRect &bounds);
    void removeHandles(void);

    // move handles by translating
    void moveHandles(QPoint delta);

    // transform to/from zoomed coordinates by applying world transform
    QPoint convertZoom(QPoint p, bool to);
    QRect convertZoom(QRect r, bool to);
    
    // return bounding rectangle for a list of canvas items
    QRect listBounds(Q3CanvasItemList* list);

    // zoom factor as a percentage. zooms other than 100 will suffer performance penalty
    // locally and in the Qt library because extra transformations must be performed
    int m_zoom;
};

#endif // DIGITVIEW_H
