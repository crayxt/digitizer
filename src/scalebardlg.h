/***************************************************************************
                          scalebardlg.h  -  description
                             -------------------
    begin                : Tue Dec 31 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: scalebardlg.h,v $
    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.5  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.3  2004/02/23 21:11:58  markmitch
    Internationalization support

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

#ifndef SCALEBARDLG_H
#define SCALEBARDLG_H

#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qvalidator.h>

class DigitDoc;

// when a scale bar is created, this dialog appears so the user can immediately
// enter in the length of the scale bar
class ScaleBarDlg : public QDialog
{
  Q_OBJECT
  
  public: 

    ScaleBarDlg(DigitDoc* doc, double length);
    ~ScaleBarDlg();

    const QString length(void) { return editLength->text(); }
    
  private:

    QLabel* labelLength;
    QLineEdit* editLength;
    QDoubleValidator* doubleValidator;
    QPushButton* buttonOk;
    QPushButton* buttonCancel;

    DigitDoc* doc;
};

#endif // SCALEBARDLG_H
