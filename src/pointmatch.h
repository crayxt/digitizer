/***************************************************************************
                          pointmatch.h  -  description
                             -------------------
    begin                : Tue Jan 6 2003
    copyright            : (C) 2003 by 
    email                : mmdigitizer@earthlink.net
    $Log: pointmatch.h,v $
    Revision 1.10  2007/01/03 01:54:13  markmitch
    Processing... dialog that required multithreading

    Revision 1.9  2006/12/16 21:29:59  markmitch
    Array size bug

    Revision 1.8  2006/12/16 21:16:36  markmitch
    Memory and speed optimizations for point matching

    Revision 1.7  2006/12/13 08:32:17  markmitch
    Fast convolution point match works, with build issues still

    Revision 1.6  2006/12/08 06:32:46  markmitch
    Midway through incorporating fftw3

    Revision 1.5  2006/10/08 06:41:50  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.8  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.6  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.5  2004/01/14 06:54:38  markmitch
    Point match works well and has documentation

    Revision 1.4  2004/01/13 18:53:33  markmitch
    Point match works but needs bells and whistles

    Revision 1.3  2004/01/13 17:54:06  markmitch
    Testing point match

    Revision 1.2  2004/01/08 06:48:35  markmitch
    Reworked menu icons look great

    Revision 1.1  2004/01/07 07:48:07  markmitch
    Implementing point match


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef POINTMATCH_H
#define POINTMATCH_H

#include <qimage.h>
#include <qcolor.h>
#include <qpoint.h>
#include <q3intdict.h>
#include <q3ptrlist.h>
#include <qthread.h>
//Added by qt3to4:
#include <QList>
#include <Q3PtrCollection>
#include <QPolygon>

#include "digitdef.h"
#include "digitdebug.h"

#include "fftw3.h"

class Match;

// pointer list that also sorts Match objects by xTheta coordinate
template <class T>
class MatchPtrList: public Q3PtrList<T>
{
  protected:

    virtual int compareItems(Q3PtrCollection::Item item1, Q3PtrCollection::Item item2)
    {
      PointMatchTriplet* p1 = (PointMatchTriplet*) item1;
      PointMatchTriplet* p2 = (PointMatchTriplet*) item2;
      if (p1->correlation > p2->correlation)
        return -1;
      else if (p1->correlation < p2->correlation)
        return 1;
      else
        return 0;
    }
};

// the point lists are pointer lists (versus value lists) so that, for brief
// intervals, there can be multiple pointsets that share the same points. Further
// information can be found in the PointSets comments
typedef MatchPtrList<PointMatchTriplet> PointMatchList;

// this class searches through the original or processed image and 
// isolates candidate match points. the matches are sorted by
// quality of match
class PointMatch
{
  public:
  
    PointMatch();
    ~PointMatch();

    // recursively isolate the "on" pixels around (x,y). return true if pixel at (x,y) was on
    bool isolateSampleMatchPoint(QPolygon * samplePointPixels,
      const QImage &image, PointMatchSettings settings,
      int xStart, int yStart, int x, int y);

    // create document points that match the sample point under the cursor
    static void matchSamplePoint(const QImage &imageProcessed,
                                 PointMatchSettings settings, 
                                 const QPolygon &samplePointPixels,
                                 const QPolygon &pointsExisting, 
                                 QList<PointMatchTriplet>* pointsCreated);

};

#endif // POINTMATCH_H
