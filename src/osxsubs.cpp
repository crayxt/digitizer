/***************************************************************************
                          osxsubs.cpp  -  description
                             -------------------
    begin                : Sun Nov 7 2004
    copyright            : (C) 2004 by
    email                : mmdigitizer@earthlink.net
    $Log: osxsubs.cpp,v $
    Revision 1.1  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.3  2004/11/11 06:22:18  markmitch
    Pathological case on Mac computer

    Revision 1.2  2004/11/09 06:48:32  markmitch
    Debugging for OSX port

    Revision 1.1  2004/11/07 18:50:16  markmitch
    OSX subroutines


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <qmessagebox.h>

#include "osxsubs.h"

#ifdef Q_OS_MACX

#include <CoreFoundation/CoreFoundation.h>

QDir userManualPath()
{
  CFURLRef pluginRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
  CFStringRef macPath = CFURLCopyFileSystemPath(pluginRef,
                                                kCFURLPOSIXPathStyle);
  const char *pathPtr = CFStringGetCStringPtr(macPath,
                                              CFStringGetSystemEncoding());

  QString p(pathPtr);
  p += "/Contents/Resources/usermanual";

  return QDir(p);
}

#endif
