/***************************************************************************
                          matchset.h  -  description
                             -------------------
    begin                : Mon Jan 12 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@gmail.com

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
#include <Q3ValueList>

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
    void acceptedPoints(Q3ValueList<QPoint>* acceptedPoints);
    
    // create one canvas item for each matched point
    void addCreatedPointsToCanvas(Q3Canvas* canvas, PointSetStyle style,
      PointMatchSettings settings, const Q3ValueList<PointMatchTriplet>* pointsCreated,
      Q3ValueList<QRect>* updateRectList);

    // destroy all objects, releasing allocated memory
    void clear(Q3ValueList<QRect>* updateRectList);

    // add accepted, add rejected or remove one match point, returning true if a point's
    // state was changed
    bool matchPointAccept(Q3ValueList<QRect>* updateRectList);
    bool matchPointReject(Q3ValueList<QRect>* updateRectList);
    bool matchPointRemove(Q3ValueList<QRect>* updateRectList);

    // show style change on screen
    void setPointSetStyle(PointSetStyle style);
    
  private:

    // highlight maintenance
    Q3CanvasRectangle* makeHighlight(Color color);
    void moveHighlights(Q3ValueList<QRect>* updateRectList);

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
