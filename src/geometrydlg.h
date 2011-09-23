/***************************************************************************
                          geometrydlg.h  -  description
                             -------------------
    begin                : Fri Nov 1 2002
    copyright            : (C) 2002 by
    email                : mmdigitizer@earthlink.net
    $Log: geometrydlg.h,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.14  2004/11/09 06:47:02  markmitch
    Prevent unnecessary grid updates

    Revision 1.13  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.11  2004/09/16 03:13:53  markmitch
    Document all new features. Paste works i Windows

    Revision 1.10  2004/09/15 04:43:28  markmitch
    Drag export geometry. Drag import image

    Revision 1.9  2004/09/14 16:22:32  markmitch
    Geometry window drag works

    Revision 1.8  2004/09/13 08:32:32  markmitch
    Table-based geometry windows

    Revision 1.7  2003/12/29 06:55:10  markmitch
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

#ifndef GEOMETRYDLG_H
#define GEOMETRYDLG_H

#include <qdialog.h>
#include <qlayout.h>
#include <q3table.h>
#include <qstringlist.h>
//Added by qt3to4:
#include <QResizeEvent>
#include <QMoveEvent>
#include <QKeyEvent>
#include <QHideEvent>
#include <Q3GridLayout>

#include "geometrywindowitem.h"

class DigitDoc;

// this dialog box just displays the geometry information for the currently
// selected curve or measure pointset. this dialog is unique among the dialog boxes
// in that:
// (1) it is resizable (the other dialogs would require too much work)
// (2) it displays only so there are no ok and cancel buttons (they would be equivalent)
// (3) it is modeless
class GeometryDlg : public QDialog
{
  Q_OBJECT
    
  public:

    GeometryDlg(QWidget* parent, bool curve);
    ~GeometryDlg();

    // replace existing contents of table
    void displayGeometryInfo(GeometryWindowItemList& rInfo);

    // write selected items into a string with the specified delimiter
    QString extractSelectedItems(QString delimiter);

  signals:

    // user clicked on close button in title bar
    void hideGeometry();

  protected:

    // forward the hide event to the main window
    virtual void hideEvent(QHideEvent* e);
  
    // geometry windows move and resize events are caught and the geometries are saved
    virtual void moveEvent(QMoveEvent* e);
    virtual void resizeEvent(QResizeEvent* e);

  private:

    // subclass to override dragObject method
    class InfoTable : public Q3Table
    {
      public:

        InfoTable(GeometryDlg* parent);

      protected:
      
        // dragging
        virtual Q3DragObject* dragObject();

      // for copying to clipboard
      virtual void keyPressEvent(QKeyEvent* e);
    
      private:

        GeometryDlg* parent;
      
    };
     
    // true for curve pointsets, false for measure pointsets
    bool curve;

    // remove all content from table. the table items cannot be deleted
    void clearTable();

    // define size of table before items are added
    void setRowColumnCount(GeometryWindowItemList& rInfo);

    // merge new items into table
    void addNewItemsToTable(GeometryWindowItemList& rInfo);

    // get bounds of selected items. lower limits are inclusive and upper limits are exclusive
    void getSelectedItemsBounds(int& rowBegin, int& colBegin, int& rowEnd, int& colEnd);

    // returns translated string with "curve" replaced by "measure" if curve is false
    QString curveReplace(const char* text);

    // autolayout
    Q3GridLayout* layout;
        
    // scrollable list box displays all geometry information
    InfoTable* infoTable;

    // items that are currently displayed. these are used to prevent unnecessary refreshes
    GeometryWindowItemList displayedInfo;
    
};

#endif // GEOMETRYDLG_H
