/***************************************************************************
                          digitdef.cpp  -  description
                             -------------------
    begin                : Tue Oct 29 14:43:44 PST 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: digitdef.cpp,v $
    Revision 1.9  2007/04/10 05:12:42  markmitch
    Arrow keys move selection

    Revision 1.8  2006/12/28 09:03:37  markmitch
    Windows build works

    Revision 1.7  2006/12/13 08:32:17  markmitch
    Fast convolution point match works, with build issues still

    Revision 1.6  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.4.2.4  2006/09/29 03:53:20  markmitch
    Version 3 commit with backwards compatibility

    Revision 1.4.2.3  2006/09/24 06:07:14  markmitch
    New date/time converter

    Revision 1.4.2.2  2006/03/14 07:10:34  markmitch
    Point Match on graphs with lines no longer crashes

    Revision 1.4.2.1  2006/03/07 06:13:45  markmitch
    Version 2.14. Help window buttons visible. Lazy segment scanning

    Revision 1.4  2005/03/21 06:51:14  markmitch
    Version 2.13

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.14  2004/11/18 05:40:45  markmitch
    Adjust precision of exported results to show significant digits

    Revision 1.13  2004/10/28 04:54:31  markmitch
    Scan for axes

    Revision 1.12  2004/10/18 23:00:53  markmitch
    Version numbers are now strings since 2.1 is not 2.10. Fixed displaying wrong points with multiple documents

    Revision 1.11  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.9  2004/09/09 05:33:44  markmitch
    Invoker in work. Windows upgrade to 3.3.3

    Revision 1.8  2003/12/29 06:55:10  markmitch
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

#include "digitdef.h"
#include "main.h"

QString VersionNumber;
QStringList VersionNumbersSupported;

// globals that really should not belong to any class. the goal is to
// localize the simple user datatype code, with more complicated user
// datatypes getting their own classes
QStringList GridSetStrings;

// kludge for freeware Qt 2.3.1 so window captions work
#if defined(WIN32)
const char* freewareCaption = " [Qt]";
#else
const char* freewareCaption = "";
#endif

QString delimiter(ExportDelimiters del)
{
  switch(del)
  {
    case Commas:
    default:
      return QString(",");
    case Spaces:
      return QString(" ");
    case Tabs:
      return QString("\t");
  }
}

void initGlobals()
{
  GridSetStrings.append("Count");
  GridSetStrings.append("Start");
  GridSetStrings.append("Step");
  GridSetStrings.append("Stop");

  // following asserts guarantee the QStringList will effectively work as an array. there
  // is no QStringArray, and QStringList is supported by many widgets
  ASSERT_ENGAUGE(GridSetStrings.findIndex("Count") == AllButCount);
  ASSERT_ENGAUGE(GridSetStrings.findIndex("Start") == AllButStart);
  ASSERT_ENGAUGE(GridSetStrings.findIndex("Step") == AllButStep);
  ASSERT_ENGAUGE(GridSetStrings.findIndex("Stop") == AllButStop);

  VersionNumber = QString("5.0");
  VersionNumbersSupported <<
    "2.0" << "2.1" << "2.2" << "2.3" << "2.4" << "2.5" << "2.6" << "2.7" <<  "2.8" << 
    "2.9" << "2.10" << "2.11" << "2.12" << "2.13" << "2.14" << "2.15" << "3.0" << 
    "4.0" << "4.1" <<
    "5.0";
}

mmUnits mmUnitize(CoordSettings coord)
{
  if (coord.frame == Cartesian)
    return mmCartesian;
  else
  {
    // polar coordinates
    if (coord.thetaUnits == ThetaDegrees)
     return mmDegrees;
    else if (coord.thetaUnits == ThetaGradians)
      return mmGradians;
    else
      return mmRadians;
  }
}
