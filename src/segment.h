/***************************************************************************
                          segment.h  -  description
                             -------------------
    begin                : Wed Nov 20 2002
    copyright            : (C) 2002 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: segment.h,v $
    Revision 1.5  2006/10/08 06:41:50  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:07  markmitch
    After KDevelop 3 restructuring

    Revision 1.13  2004/10/15 03:30:36  markmitch
    Fill corners option in segment fill

    Revision 1.12  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.10  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.9  2003/12/29 06:55:10  markmitch
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

#ifndef SEGMENT_H
#define SEGMENT_H

#include <q3canvas.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <QList>

#include "digitdef.h"

class Segment;

// this class is a special case the standard QCanvasLine for segments, and
// has its own rtti value
class SegmentLine : public Q3CanvasLine
{
  public:

    SegmentLine(Q3Canvas* canvas, Segment* segment);
    ~SegmentLine();

    int rtti(void) const { return Rtti_SegmentLine; }

    Segment* segment(void) { return m_segment; }
    
  private:

    Segment* m_segment;  
};

// this class is a container for all of the segments. a segment is a set
// of linked lines that run along a curve in the original image. the
// main complication is that curves in the original image cross each other
// and other things like grid lines. rather than invent artificial
// intelligence (the next software project), we rely on the user to link
// multiple segments together to get points along the entire curve length
class Segment
{
  public: 

    Segment(Q3Canvas* canvas, int y);
    ~Segment();

    // add some more pixels in a new column to an active segment
    void appendColumn(int x, int y, SegmentSettings seg);

    // show or hide segment
    void showSegment(bool toggle, SegmentSettings seg, QList<QRect>* updateRectList);

    // get methods for length in pixels and in lines
    double length(void) { return m_length; }
    int lineCount(void) { return m_lines.count(); }

    // try to compress a segment that was just completed, by folding together line from
    // point i to point i+1, with the line from i+1 to i+2, then the line from i+2 to i+3,
    // until one of the points is more than a half pixel from the folded line. this should
    // save memory and improve user interface responsiveness
    void removeUnneededLines(int* foldedLines);

    // returns canvas item list of segment lines as downcasted canvas lines
    Q3CanvasItemList lines(void);

    // create evenly spaced points along the segment
    QList<QPoint> fillPoints(SegmentSettings seg);

    // get and set methods for segment settings
    void setSettings(SegmentSettings settings);
    
    // display debug information for this segment
    void dump(void);
        
  private:

    Q3Canvas* canvas;
    
    // y value of last point which is in previous column
    int yLast;
    
    // this segment is drawn as a series of line segments
    Q3PtrList<SegmentLine> m_lines;

    // total length of lines owned by this segment, as floating point to allow fractional increments
    double m_length;

    // while filling corners, create a point if any of the following are true:
    // -it is the first point of the any line segment
    // -it is different than the previous point
    // while not filling corners, create a point if any of the following are true:
    // -it is the first point of the first line segment
    // -it is different than the previous point
    void createAcceptablePoint(bool* pFirst, QList<QPoint>* pList,
      double* xPrev, double* yPrev, double x, double y);

    // create evenly spaced points along the segment
    QList<QPoint> fillPointsFillingCorners(SegmentSettings seg);
    QList<QPoint> fillPointsWithoutFillingCorners(SegmentSettings seg);
      
    // return true if point are a half pixel or less away from a line
    bool pointIsCloseToLine(double xLeft, double yLeft, double xInt, double yInt,
      double xRight, double yRight);
    bool pointsAreCloseToLine(double xLeft, double yLeft, QList<QPoint> removedPoints,
      double xRight, double yRight);
        
};

#endif // SEGMENT_H
