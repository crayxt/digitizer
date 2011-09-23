/***************************************************************************
                          curvecmb.h  -  description
                             -------------------
    begin                : Thu Oct 31 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: curvecmb.h,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.7  2004/10/07 07:55:47  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.6  2004/10/05 04:00:48  markmitch
    Combobox color reflects digitize state

    Revision 1.5  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.3  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.2  2003/12/29 06:55:10  markmitch
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

#ifndef CURVECMB_H
#define CURVECMB_H

#include <qwidget.h>
#include <qcombobox.h>

#include "digitdoc.h"

// this combobox in draw toolbar displays the currently active curve, if in
// curve mode. otherwise this is grayed out
class CurveCmb : public QComboBox
{
  Q_OBJECT

  public:
  
    CurveCmb(QWidget* parent);
    ~CurveCmb();

    // load curve names from a document
    void attachToDocument(DigitDoc* doc);
    
  private slots:

    // change cursor to curve point mode
    void slotComboCurve(bool toggle);
    // change cursor to noncurve point mode
    void slotComboNotCurve(bool toggle);
};

#endif // CURVECMB_H
