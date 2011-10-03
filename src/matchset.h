/***************************************************************************
                          matchset.h  -  description
                             -------------------
    begin                : Mon Jan 12 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: matchset.h,v $
    Revision 1.6  2006/12/20 08:20:26  markmitch
    Rework of point matching to handle skipping

    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

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

#ifndef MATCHSET_H
#define MATCHSET_H

#include <q3canvas.h>
#include <q3textstream.h>
#include <q3ptrlist.h>
//Added by qt3to4:
#include <QList>

#include "digitdef.h"

class Highlight;
class Match;

// this class contains all Match class objects, and parallels the
// PointSet class, although this is much more simple. the Match
// objects owned by this class were originally owned by a QArray,
// but that created dependency problems in the header file
class MatchSet
{
  public:

    MatchSet();
    ~MatchSet();

    // return currently accepted points
    void acceptedPoints(QList<QPoint>* acceptedPoints);
    
    // create one canvas item for each matched point
    void addCreatedPointsToCanvas(Q3Canvas* canvas, PointSetStyle style,
      PointMatchSettings settings, const QList<PointMatchTriplet>* pointsCreated,
      QList<QRect>* updateRectList);

    // destroy all objects, releasing allocated memory
    void clear(QList<QRect>* updateRectList);

    // add accepted, add rejected or remove one match point, returning true if a point's
    // state was changed
    bool matchPointAccept(QList<QRect>* updateRectList);
    bool matchPointReject(QList<QRect>* updateRectList);
    bool matchPointRemove(QList<QRect>* updateRectList);

    // show style change on screen
    void setPointSetStyle(PointSetStyle style);
    
  private:

    // highlight maintenance
    Q3CanvasRectangle* makeHighlight(Color color);
    void moveHighlights(QList<QRect>* updateRectList);

    Q3Canvas* m_canvas;
    PointMatchSettings m_settings;

    // pointer list of Match objects. QArray might have been better, but QArray
    // requires default constructors for its objects, but QCanvasItems require
    // pointer to canvas in all of the constructors. speed is not much of an issue
    // since only one search is performed after each keypress speed
    int m_matches;
    Q3PtrList<Match> m_matchList;

    // highlight the candidate point. QCanvasEllipse is not an option since the pen 
    // is always NoPen
    Highlight* m_highlightCandidate;
};

#endif // MATCHSET_H
