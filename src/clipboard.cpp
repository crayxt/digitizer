/***************************************************************************
                          clipboard.cpp  -  description
                             -------------------
    begin                : Mon Dec 9 2002
    copyright            : (C) 2002 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: clipboard.cpp,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.9  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.7  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.6  2003/12/29 06:55:10  markmitch
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

#include "clipboard.h"
#include "digitdebug.h"
//Added by qt3to4:
#include <Q3ValueList>

Clipboard* Clipboard::m_clipboard = (Clipboard*) 0;

Clipboard::Clipboard()
{
  DigitDebug::ctor(QString("clipboard ") + QString::number((ulong) this, 16));
}

Clipboard::~Clipboard()
{
  DigitDebug::dtor(QString("clipboard ") + QString::number((ulong) this, 16));
}

void Clipboard::addPoint(int xScreen, int yScreen)
{
  // note that the point loses its association with any pointset when added to the clipboard
  // TODO - allow reassigning a point (which may be from a paste) to another pointset
  m_contents.append(QPoint(xScreen, yScreen));
}

void Clipboard::dump()
{
  Q3ValueList<QPoint>::iterator itr;
  for (itr = m_contents.begin(); itr != m_contents.end(); ++itr)
    qDebug("%d\t%d\n", (*itr).x(), (*itr).y());
}
