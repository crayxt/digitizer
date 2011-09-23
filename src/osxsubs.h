/***************************************************************************
                          osxsubs.h  -  description
                             -------------------
    begin                : Sun Nov 7 2004
    copyright            : (C) 2004 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: osxsubs.h,v $
    Revision 1.1  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

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

#ifndef OSXSUBS_H
#define OSXSUBS_H

#include <qdir.h>

#ifdef Q_OS_MACX

extern QDir userManualPath();

#endif // Q_OS_MACX

#endif // OSXSUBS_H
