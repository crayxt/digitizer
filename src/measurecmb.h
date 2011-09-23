/***************************************************************************
                          measurecmb.h  -  description
                             -------------------
    begin                : Fri Dec 27 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: measurecmb.h,v $
    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.7  2004/10/07 07:55:48  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.6  2004/10/05 04:00:55  markmitch
    Combobox color reflects digitize state

    Revision 1.5  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.3  2004/09/12 22:29:21  markmitch
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

#ifndef MEASURECMB_H
#define MEASURECMB_H

#include <qwidget.h>
#include <qcombobox.h>

#include "digitdoc.h"

// this combobox in draw toolbar displays the currently active measure, if in
// measure mode. otherwise this is grayed out
class MeasureCmb : public QComboBox
{
  Q_OBJECT

  public:
  
    MeasureCmb(QWidget* parent);
    ~MeasureCmb();

    // load measure names from a document
    void attachToDocument(DigitDoc* doc);

  private slots:

    // change cursor to measure point mode
    void slotComboMeasure(bool toggle);
    // change cursor to nonmeasure point mode
    void slotComboNotMeasure(bool toggle);
};

#endif // MEASURECMB_H
