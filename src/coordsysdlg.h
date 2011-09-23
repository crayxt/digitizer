/***************************************************************************
                          coordsysdlg.h  -  description
                             -------------------
    begin                : Wed Oct 30 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: coordsysdlg.h,v $
    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.2  2006/09/13 06:17:02  markmitch
    Polar plot with origin offset works. Invalid axis/scale point combos prevented

    Revision 1.3.2.1  2006/09/08 07:03:36  markmitch
    Nonzero origin radius. Bugs: Not serialized, maybe nonzero+log issue

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.4  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

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

#ifndef COORDSYSDLG_H
#define COORDSYSDLG_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <q3buttongroup.h>
#include <qradiobutton.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qvalidator.h>

#include "digitdef.h"

// this dialog box class edits a document's axes information
class CoordSysDlg : public QDialog
{
  Q_OBJECT

  public:
  
    CoordSysDlg(QString title, CoordSettings* settings);
    ~CoordSysDlg();

  private slots:

    void slotCartesian(bool toggle);
    void slotPolar(bool toggle);
    void slotOriginRadius(const QString &originRadius);
    void slotLinearX(bool toggle);
    void slotLogX(bool toggle);
    void slotLinearY(bool toggle);
    void slotLogY(bool toggle);
    void slotDegrees(bool toggle);
    void slotGradians(bool toggle);
    void slotRadians(bool toggle);
    void slotWhat(void);
    
  private:

    // enable or disable buttons as appropriate
    void toggleActions();
    
    CoordSettings* settings;

    Q3ButtonGroup* groupCoords;
    QRadioButton* buttonCartesian;
    QRadioButton* buttonPolar;
   
    Q3ButtonGroup* groupX;
    QRadioButton* buttonLinearX;
    QRadioButton* buttonLogX;

    Q3ButtonGroup* groupY;
    QRadioButton* buttonLinearY;
    QRadioButton* buttonLogY;

    Q3ButtonGroup* groupPolar;
    QLabel* labelThetaUnits;
    QRadioButton* buttonDegrees;
    QRadioButton* buttonGradians;
    QRadioButton* buttonRadians;
    QLabel* labelOriginRadius;
    QLineEdit* editOriginRadius;
    QDoubleValidator* validatorOriginRadius;
    
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* buttonWhat;
};

#endif // COORDSYSDLG_H
