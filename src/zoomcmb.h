/***************************************************************************
                          zoomcmb.h  -  description
                             -------------------
    begin                : Sat Dec 7 2002
    copyright            : (C) 2002 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: zoomcmb.h,v $
    Revision 1.3  2005/03/20 01:47:07  markmitch
    After KDevelop 3 restructuring

    Revision 1.7  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.5  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.4  2004/02/23 21:11:58  markmitch
    Internationalization support

    Revision 1.3  2003/12/29 06:55:10  markmitch
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

#ifndef ZOOMCMB_H
#define ZOOMCMB_H

#include <QComboBox>
#include <qvalidator.h>
//Added by qt3to4:
#include <QKeyEvent>

// zoom combobox in zoom toolbar shows and modifies zoom setting of
// currently active window
class ZoomCmb : public QComboBox
{
  Q_OBJECT
  
  public: 

    ZoomCmb(QWidget* parent);
    ~ZoomCmb();

    // called when changing focus to another window. show union of default list and
    // this value
    void setZoom(int z);
    
  private:

    // send the zoom value to the view when carriage return is pressed
    virtual void keyPressEvent(QKeyEvent* e);

    QRegExpValidator* validator;
    
};

#endif // ZOOMCMB_H
