/***************************************************************************
                          geometrywindowitem.cpp  -  description
                             -------------------
    begin                : Sun Sep 12 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: geometrywindowitem.cpp,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.5  2004/11/09 08:03:21  markmitch
    Return value in copy constructor

    Revision 1.4  2004/11/09 06:47:02  markmitch
    Prevent unnecessary grid updates

    Revision 1.3  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.1  2004/09/13 08:32:32  markmitch
    Table-based geometry windows


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "geometrywindowitem.h"

GeometryWindowItem::GeometryWindowItem() :
  m_row(0),
  m_column(0)
{
}

GeometryWindowItem::GeometryWindowItem(int row, int column, QString entry) :
  m_row(row),
  m_column(column),
  m_entry(entry)
{
}

GeometryWindowItem::GeometryWindowItem(const GeometryWindowItem& old)
{
  m_row = old.row();
  m_column = old.column();
  m_entry = old.entry();
}

GeometryWindowItem& GeometryWindowItem::operator=(const GeometryWindowItem& old)
{
  m_row = old.row();
  m_column = old.column();
  m_entry = old.entry();  

  return *this;
}

bool GeometryWindowItem::operator==(const GeometryWindowItem& other) const
{
  return ((m_row == other.row()) &&
    (m_column == other.column()) &&
    (m_entry == other.entry()));
}
    
int GeometryWindowItem::row() const
{
  return m_row;
}

int GeometryWindowItem::column() const
{
  return m_column;
}

QString GeometryWindowItem::entry() const
{
  return m_entry;
}
