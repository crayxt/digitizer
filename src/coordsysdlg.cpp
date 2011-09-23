/***************************************************************************
                          coordsysdlg.cpp  -  description
                             -------------------
    begin                : Wed Oct 30 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: coordsysdlg.cpp,v $
    Revision 1.6  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.3  2006/09/29 03:53:20  markmitch
    Version 3 commit with backwards compatibility

    Revision 1.3.2.2  2006/09/13 06:17:02  markmitch
    Polar plot with origin offset works. Invalid axis/scale point combos prevented

    Revision 1.3.2.1  2006/09/08 07:03:36  markmitch
    Nonzero origin radius. Bugs: Not serialized, maybe nonzero+log issue

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.13  2004/11/07 06:23:54  markmitch
    Narrow buttons get chopped in OSX

    Revision 1.12  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.10  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.9  2003/12/29 06:55:10  markmitch
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

#include <q3whatsthis.h>
#include <qtooltip.h>
//Added by qt3to4:
#include <QPixmap>
#include <QLabel>

#include "coordsysdlg.h"
#include "main.h"
#include "img/whatsthis.xpm"
#include "digitdebug.h"

CoordSysDlg::CoordSysDlg(QString title, CoordSettings* settings) :
  QDialog(0, "coordsysdlg", true),
  settings(settings)
{
  DigitDebug::ctor(QString("coordsysdlg ") + QString::number((ulong) this, 16));
  
  setCaption(tr("Coordinate System - [%1]%2")
    .arg(title)
    .arg(freewareCaption));

  setFixedSize(340, 360);

  // coordinate reference frame
  groupCoords = new Q3ButtonGroup(QString(tr("Coordinates")), this);
  CHECK_PTR_ENGAUGE(groupCoords);
  groupCoords->setGeometry(10, 10, 320, 80);

  buttonCartesian = new QRadioButton(QString(tr("Cartesian (X and Y)")), groupCoords);
  CHECK_PTR_ENGAUGE(buttonCartesian);
  buttonCartesian->setGeometry(10, 30, 210, 20);
  Q3WhatsThis::add(buttonCartesian, QString(tr("Select cartesian coordinates.\n\n"
    "The X and Y coordinates will be used")));
  connect(buttonCartesian, SIGNAL(toggled(bool)), this, SLOT(slotCartesian(bool)));

  buttonPolar = new QRadioButton(QString(tr("Polar (Theta and R)")), groupCoords);
  CHECK_PTR_ENGAUGE(buttonPolar);
  buttonPolar->setGeometry(10, 50, 210, 20);
  Q3WhatsThis::add(buttonPolar, QString(tr("Select polar coordinates.\n\n"
    "The Theta and R coordinates will be used.\n\n"
    "Polar coordinates are not allowed with log scale for Theta")));
  connect(buttonPolar, SIGNAL(toggled(bool)), this, SLOT(slotPolar(bool)));

  // x/theta
  groupX = new Q3ButtonGroup(QString(tr("X/Theta")), this);
  CHECK_PTR_ENGAUGE(groupX);
  groupX->setGeometry(10, 100, 145, 80);

  buttonLinearX = new QRadioButton(QString(tr("Linear")), groupX);
  CHECK_PTR_ENGAUGE(buttonLinearX);
  buttonLinearX->setGeometry(10, 30, 80, 20);
  Q3WhatsThis::add(buttonLinearX, QString(tr("Specifies linear scale for the X or Theta coordinate")));
  connect(buttonLinearX, SIGNAL(toggled(bool)), this, SLOT(slotLinearX(bool)));

  buttonLogX = new QRadioButton(QString(tr("Log")), groupX);
  CHECK_PTR_ENGAUGE(buttonLogX);
  buttonLogX->setGeometry(10, 50, 80, 20);
  Q3WhatsThis::add(buttonLogX, QString(tr("Specifies logarithmic scale for the X coordinate.\n\n"
    "Log scale is not allowed for the Theta coordinate")));
  connect(buttonLogX, SIGNAL(toggled(bool)), this, SLOT(slotLogX(bool)));

  // y/r
  groupY = new Q3ButtonGroup(QString(tr("Y/R")), this);
  CHECK_PTR_ENGAUGE(groupY);
  groupY->setGeometry(185, 100, 145, 80);
  
  buttonLinearY = new QRadioButton(QString(tr("Linear")), groupY);
  CHECK_PTR_ENGAUGE(buttonLinearY);
  buttonLinearY->setGeometry(10, 30, 80, 20);
  Q3WhatsThis::add(buttonLinearY, QString(tr("Specifies linear scale for the Y or R coordinate")));
  connect(buttonLinearY, SIGNAL(toggled(bool)), this, SLOT(slotLinearY(bool)));

  buttonLogY = new QRadioButton(QString(tr("Log")), groupY);
  CHECK_PTR_ENGAUGE(buttonLogY);
  buttonLogY->setGeometry(10, 50, 80, 20);
  Q3WhatsThis::add(buttonLogY, QString(tr("Specifies logarithmic scale for the Y or R coordinate")));
  connect(buttonLogY, SIGNAL(toggled(bool)), this, SLOT(slotLogY(bool)));

  // polar group
  groupPolar = new Q3ButtonGroup(QString(tr("Polar Coordinates")), this);
  CHECK_PTR_ENGAUGE(groupPolar);
  groupPolar->setGeometry(10, 190, 320, 120);

  // theta units in polar group
  labelThetaUnits = new QLabel(QString(tr("Theta Units:")), groupPolar);
  CHECK_PTR_ENGAUGE(labelThetaUnits);
  labelThetaUnits->setGeometry(10, 30, 80, 20);

  buttonDegrees = new QRadioButton(QString(tr("Degrees:")), groupPolar);
  CHECK_PTR_ENGAUGE(buttonDegrees);
  buttonDegrees->setGeometry(10, 50, 210, 20);
  Q3WhatsThis::add(buttonDegrees, QString(tr("Specifies degrees for the Theta coordinate.\n\n"
    "This does not apply to the cartesian coordinate X")));
  connect(buttonDegrees, SIGNAL(toggled(bool)), this, SLOT(slotDegrees(bool)));

  buttonGradians = new QRadioButton(QString(tr("Gradians")), groupPolar);
  CHECK_PTR_ENGAUGE(buttonGradians);
  buttonGradians->setGeometry(10, 70, 210, 20);
  Q3WhatsThis::add(buttonGradians, QString("Specifies gradians for the Theta coordinate.\n\n"
    "This does not apply to the cartesian coordinate X"));
  connect(buttonGradians, SIGNAL(toggled(bool)), this, SLOT(slotGradians(bool)));

  buttonRadians = new QRadioButton(QString(tr("Radians")), groupPolar);
  CHECK_PTR_ENGAUGE(buttonRadians);
  buttonRadians->setGeometry(10, 90, 210, 20);
  Q3WhatsThis::add(buttonRadians, QString("Specifies radians for the Theta coordinate.\n\n"
    "This does not apply to the cartesian coordinate X"));
  connect(buttonRadians, SIGNAL(toggled(bool)), this, SLOT(slotRadians(bool)));

  // polar origin radius in polar group
  labelOriginRadius = new QLabel(QString(tr("Origin Radius:")), groupPolar);
  CHECK_PTR_ENGAUGE(labelOriginRadius);
  labelOriginRadius->setGeometry(230, 30, 80, 20);
  
  editOriginRadius = new QLineEdit(groupPolar);
  CHECK_PTR_ENGAUGE(editOriginRadius);
  editOriginRadius->setText(QString("%1").arg(settings->originRadius));
  editOriginRadius->setGeometry(230, 50, 80, 20);
  Q3WhatsThis::add(editOriginRadius, QString(tr("Specify radius value at origin.\n\n"
    "Normally the radius at the origin is 0, but a nonzero value may be applied if the radial units are decibels.")));
  validatorOriginRadius = new QDoubleValidator(editOriginRadius);
  CHECK_PTR_ENGAUGE(validatorOriginRadius);
  validatorOriginRadius->setBottom(0.0);
  editOriginRadius->setValidator(validatorOriginRadius);
  connect(editOriginRadius, SIGNAL(textChanged(const QString &)), this, SLOT(slotOriginRadius(const QString &)));

  // navigation buttons
  buttonOk = new QPushButton(tr("OK"), this);
  CHECK_PTR_ENGAUGE(buttonOk);
  buttonOk->setGeometry(10, 320, 100, 30);
  connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));

  buttonCancel = new QPushButton(tr("Cancel"), this);
  CHECK_PTR_ENGAUGE(buttonCancel);
  buttonCancel->setGeometry(140, 320, 100, 30);
  connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

  buttonWhat = new QPushButton(this);
  CHECK_PTR_ENGAUGE(buttonWhat);
  buttonWhat->setPixmap(QPixmap(whatsthis_xpm));
  buttonWhat->setGeometry(270, 320, 60, 30);
  QToolTip::add(buttonWhat, QString(tr("What's this?")));
  connect(buttonWhat, SIGNAL(clicked()), this, SLOT(slotWhat()));
  
  toggleActions();
}

CoordSysDlg::~CoordSysDlg()
{
  DigitDebug::dtor(QString("coordsysdlg ") + QString::number((ulong) this, 16));
  
  delete buttonOk;
  delete buttonCancel;
}

void CoordSysDlg::toggleActions()
{
  // this function is straightforward except for the following constraints:
  // (1) cannot allow polar coordinates and logx simultaneously
  // (2) need to disable the polar units buttons if cartesian coordinates are chosen

  ASSERT_ENGAUGE(settings != 0);
  ASSERT_ENGAUGE(buttonCartesian != 0);
  ASSERT_ENGAUGE(buttonPolar != 0);
  ASSERT_ENGAUGE(buttonLogX != 0);
  ASSERT_ENGAUGE(buttonDegrees != 0);
  ASSERT_ENGAUGE(buttonGradians != 0);
  ASSERT_ENGAUGE(buttonRadians != 0);
  ASSERT_ENGAUGE(editOriginRadius != 0);
  switch (settings->frame)
  {
    case Cartesian:
      buttonCartesian->setChecked(true);
      editOriginRadius->setEnabled(false);

      buttonLogX->setEnabled(true);
      buttonDegrees->setEnabled(false);
      buttonGradians->setEnabled(false);
      buttonRadians->setEnabled(false);
      break;
    case Polar:
      buttonPolar->setChecked(true);
      editOriginRadius->setEnabled(true);

      buttonLogX->setEnabled(false);
      buttonDegrees->setEnabled(true);
      buttonGradians->setEnabled(true);
      buttonRadians->setEnabled(true);
      break;
  }

  switch (settings->xThetaScale)
  {
    case Linear:
      buttonLinearX->setChecked(true);

      buttonPolar->setEnabled(true);
      break;
    case Log:
      buttonLogX->setChecked(true);

      buttonPolar->setEnabled(false);
      break;
  }

  switch (settings->yRScale)
  {
    case Linear:
      buttonLinearY->setChecked(true);
      break;
    case Log:
      buttonLogY->setChecked(true);
      break;
  }

  switch (settings->thetaUnits)
  {
    case ThetaDegrees:
      buttonDegrees->setChecked(true);
      break;
    case ThetaGradians:
      buttonGradians->setChecked(true);
      break;
    case ThetaRadians:
      buttonRadians->setChecked(true);
      break;
  }
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void CoordSysDlg::slotCartesian(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->frame != Cartesian))
  {
    settings->frame = Cartesian;
    toggleActions();
  }
}

void CoordSysDlg::slotPolar(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->frame != Polar))
  {
    settings->frame = Polar;
    toggleActions();
  }
}

void CoordSysDlg::slotLinearX(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->xThetaScale != Linear))
  {
    settings->xThetaScale = Linear;
    toggleActions();
  }
}

void CoordSysDlg::slotLogX(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->xThetaScale != Log))
  {
    settings->xThetaScale = Log;
    toggleActions();
  }
}

void CoordSysDlg::slotLinearY(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->yRScale != Linear))
  {
    settings->yRScale = Linear;
    toggleActions();
  }
}

void CoordSysDlg::slotLogY(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->yRScale != Log))
  {
    settings->yRScale = Log;
    toggleActions();
  }
}

void CoordSysDlg::slotDegrees(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->thetaUnits != ThetaDegrees))
  {
    settings->thetaUnits = ThetaDegrees;
    toggleActions();
  }
}

void CoordSysDlg::slotGradians(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->thetaUnits != ThetaGradians))
  {
    settings->thetaUnits = ThetaGradians;
    toggleActions();
  }
}

void CoordSysDlg::slotRadians(bool toggle)
{
  ASSERT_ENGAUGE(settings != 0);
  if (toggle && (settings->thetaUnits != ThetaRadians))
  {
    settings->thetaUnits = ThetaRadians;
    toggleActions();
  }
}

void CoordSysDlg::slotOriginRadius(const QString &originRadius)
{
  ASSERT_ENGAUGE(settings != 0);
  if (settings->frame == Polar)
  {
    settings->originRadius = originRadius.toDouble();
    toggleActions();
  }
}

void CoordSysDlg::slotWhat()
{
  Q3WhatsThis::enterWhatsThisMode();
}
