/***************************************************************************
                          pointmatch.cpp  -  description
                             -------------------
    begin                : Tue Jan 6 2003
    copyright            : (C) 2003 by
    email                : mmdigitizer@earthlink.net
    $Log: pointmatch.cpp,v $
    Revision 1.13  2008/05/04 16:14:41  tsrsf
    update to reflect lastest Debian package
    change outside /debian/ allow compiling without qt 3 compat headers

    Revision 1.12  2007/01/03 05:14:57  markmitch
    Use _sleep in windows

    Revision 1.11  2007/01/03 01:54:13  markmitch
    Processing... dialog that required multithreading

    Revision 1.10  2006/12/16 21:29:59  markmitch
    Array size bug

    Revision 1.9  2006/12/16 21:16:36  markmitch
    Memory and speed optimizations for point matching

    Revision 1.8  2006/12/13 08:32:17  markmitch
    Fast convolution point match works, with build issues still

    Revision 1.7  2006/12/08 06:32:46  markmitch
    Midway through incorporating fftw3

    Revision 1.6  2006/11/16 07:08:32  markmitch
    Added point match requirements

    Revision 1.5  2006/10/08 06:41:50  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.1  2006/03/14 07:10:34  markmitch
    Point Match on graphs with lines no longer crashes

    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.12  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.10  2004/07/21 15:14:24  markmitch
    Need stdlib for compile in suse

    Revision 1.9  2004/05/04 04:08:40  markmitch
    Replace abs by dabs

    Revision 1.8  2004/04/05 05:39:53  markmitch
    Remove Valgrind warning messages

    Revision 1.7  2004/03/07 16:36:52  markmitch
    Stop OSX compiler warning

    Revision 1.6  2004/01/15 08:24:48  markmitch
    Delete keypress. Documentation

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

#include <qobject.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qapplication.h>
//Added by qt3to4:
#include <Q3ValueList>

#include <math.h>
#include <stdlib.h>

#include "main.h"
#include "mmsubs.h"
#include "digitdebug.h"
#include "discretize.h"
#include "pointmatch.h"
#include "pointmatchthread.h"

PointMatch::PointMatch()
{
  DigitDebug::ctor(QString("pointmatch ") + QString::number((ulong) this, 16));
}

PointMatch::~PointMatch()
{
  DigitDebug::dtor(QString("pointmatch ") + QString::number((ulong) this, 16));
}

bool PointMatch::isolateSampleMatchPoint(QPolygon* samplePointPixels,
  const QImage &image, PointMatchSettings settings,
  int xStart, int yStart, int x, int y)
{
  if ((x < 0) || (y < 0) || (image.width() <= x) || (image.height() <= y))
    return false; // out of bounds

  Discretize discretize;
  if (!discretize.processedPixelIsOn(image, x, y))
    return false; // pixel is off

  if (dabs (x - xStart) > settings.pointSize / 2)
    return false; // point is too far from start
  if (dabs (y - yStart) > settings.pointSize / 2)
    return false; // point is too far from start

  ASSERT_ENGAUGE(samplePointPixels != 0);
  bool found = (samplePointPixels->size() > 0);
  if (found)
    found = samplePointPixels->containsPoint(QPoint(x, y), Qt::OddEvenFill); 
			//(samplePointPixels->find(QPoint(x, y)) >= 0); // n-squared search happening here
  if (found)
    return true; // already in list

  // add this point
  int newSize = samplePointPixels->size() + 1;
  //bool resized = samplePointPixels->resize(newSize);
  samplePointPixels->resize(newSize);
  //ASSERT_ENGAUGE(resized);
  samplePointPixels->setPoint(newSize - 1, x, y);

  // recurse. diagonal points are included so single-pixel wide polygonal outlines will be traversed,
  // but for a 2x speed increase we only go diagonal if the adjacent nondiagonal pixels are off
  bool right =
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x + 1, y);
  bool up =
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x, y + 1);
  bool left =
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x - 1, y);
  bool down =
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x, y - 1);
  if (!right && !up)
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x + 1, y + 1);
  if (!up && !left)
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x - 1, y + 1);
  if (!left && !down)
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x - 1, y - 1);
  if (!down && !right)
    isolateSampleMatchPoint(samplePointPixels, image, settings, xStart, yStart, x + 1, y - 1);

  return true;
}

void PointMatch::matchSamplePoint(const QImage &imageProcessed,
  PointMatchSettings settings,
  const QPolygon &samplePointPixels, const QPolygon &pointsExisting,
  Q3ValueList<PointMatchTriplet>* pointsCreated)
{
  QDialog dlg;
  dlg.setFixedSize(410, 70);
  dlg.setModal(true); // modeless would allow app to close with dialog still open!

  QLabel* labelComment = new QLabel(QObject::tr("Processing..."), &dlg);
  CHECK_PTR_ENGAUGE(labelComment);
  labelComment->setGeometry(10, 10, 390, 30);
 
  dlg.show();

  PointMatchThread thread(imageProcessed,
                          settings,
                          samplePointPixels,
                          pointsExisting);

  // start thread
  thread.start();

  const unsigned long SLEEP_IN_SECONDS = 1;
  while (!thread.isFinished())
  {
    qApp->processEvents();

#ifdef WIN32
    _sleep(SLEEP_IN_SECONDS);
#else
    sleep(SLEEP_IN_SECONDS);
#endif
  }

  *pointsCreated = thread.pointsCreated();
}
