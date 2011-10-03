/***************************************************************************
                          geometrywindowitem.h  -  description
                             -------------------
    begin                : Sun Sep 12 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: geometrywindowitem.h,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

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

#ifndef GEOMETRYWINDOWITEM_H
#define GEOMETRYWINDOWITEM_H

#include <qstring.h>
#include <QList>

// entry corresponding to one cell in the table of the curve geometry or 
// measure geometry windows
class GeometryWindowItem
{
  
  public:

    GeometryWindowItem(); // default constructor should only be used by GeometryWindowItemList
    GeometryWindowItem(int row, int column, QString entry);

    // copy and assignment constructors are required by GeometryWindowItemList
    GeometryWindowItem(const GeometryWindowItem& old);
    GeometryWindowItem& operator=(const GeometryWindowItem& old);

    // comparison operator
    bool operator==(const GeometryWindowItem& other) const;
    
    int row() const;
    int column() const;
    QString entry() const;
    
  private:

    int m_row;
    int m_column;
    QString m_entry;

};

// use value list, rather than pointer list, because it offers easy deep copies (although
// this means adding default constructor, copy and assignment operators to the items). also, the
// original pointer list implementation was probably leaking memory so value list should be safer
typedef QList<GeometryWindowItem> GeometryWindowItemList;

#endif // GEOMETRYWINDOWITEM_H
