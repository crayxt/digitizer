/***************************************************************************
                          segmentdlg.cpp  -  description
                             -------------------
    begin                : Wed Oct 30 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: segmentdlg.cpp,v $
    Revision 1.5  2006/10/08 06:41:50  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:07  markmitch
    After KDevelop 3 restructuring

    Revision 1.29  2004/11/23 05:30:06  markmitch
    Changes so segment preview works in OSX

    Revision 1.28  2004/11/21 02:41:40  markmitch
    Decouple segments creation from text entry

    Revision 1.27  2004/11/20 17:21:57  markmitch
    Connect each canvas to its parent

    Revision 1.26  2004/11/18 05:40:46  markmitch
    Adjust precision of exported results to show significant digits

    Revision 1.25  2004/11/17 08:36:07  markmitch
    OSX fix for preview window

    Revision 1.24  2004/11/07 07:06:32  markmitch
    Refresh preview differently for OSX

    Revision 1.23  2004/11/07 06:23:54  markmitch
    Narrow buttons get chopped in OSX

    Revision 1.22  2004/10/20 06:22:00  markmitch
    Prevent Windows compiler warning

    Revision 1.21  2004/10/16 04:34:17  markmitch
    Gradually curving graphs

    Revision 1.20  2004/10/15 09:27:01  markmitch
    Keep line inside image. Remove broken depth conversion

    Revision 1.19  2004/10/15 09:18:01  markmitch
    Segment settings preview reworked

    Revision 1.18  2004/10/15 03:30:36  markmitch
    Fill corners option in segment fill

    Revision 1.17  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.15  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.14  2004/09/11 05:59:18  markmitch
    First phase of settings archival

    Revision 1.13  2004/01/25 19:06:59  markmitch
    Version 2.1. Limited recursion. Default grid removal settings

    Revision 1.12  2004/01/04 08:41:00  markmitch
    Dialog for point match settings

    Revision 1.11  2003/12/29 06:55:10  markmitch
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

#include <QWhatsThis>
#include <qtooltip.h>
#include <qcolor.h>
#include <qbitmap.h>
//Added by qt3to4:
#include <QList>
#include <QPixmap>
#include <QLabel>

#include "segmentdlg.h"
#include "pointsetstyles.h"
#include "digitdebug.h"
#include "main.h"
#include "defaultsettings.h"
#include "img/whatsthis.xpm"
#include "img/segmentpreview.xpm"
#include "segments.h"
#include "segment.h"

SegmentDlg::SegmentDlg(QString title, SegmentSettings* settings) :
  QDialog(0, "segmentdlg", true),
  settings(settings)
{
  DigitDebug::ctor(QString("segmentdlg ") + QString::number((ulong) this, 16));
  
  setCaption(tr("Segments - [%1]%2")
    .arg(title)
    .arg(freewareCaption));

  setFixedSize(340, 380);

  // segment settings
  labelMinPoints = new QLabel(QString(tr("Minimum Length:")), this);
  CHECK_PTR_ENGAUGE(labelMinPoints);
  labelMinPoints->setGeometry(20, 10, 160, 30);

  editMinPoints = new QLineEdit(this);
  CHECK_PTR_ENGAUGE(editMinPoints);
  editMinPoints->setGeometry(190, 10, 130, 30);
  editMinPoints->setText(QString("%1").arg(settings->minPoints));
  QWhatsThis::add(editMinPoints, QString(tr("Select a minimum number of points in a segment.\n\n"
    "Only segments with more points will be created.\n\n"
    "This value should be as large as possible to reduce memory usage. This value has "
    "a lower limit")));
  validatorMinPoints = new QIntValidator(editMinPoints);
  CHECK_PTR_ENGAUGE(validatorMinPoints);
  editMinPoints->setValidator(validatorMinPoints);
  connect(editMinPoints, SIGNAL(textChanged(const QString &)), this, SLOT(slotMinPoints(const QString &)));

  labelPointSeparation = new QLabel(QString(tr("Point Separation:")), this);
  CHECK_PTR_ENGAUGE(labelPointSeparation);
  labelPointSeparation->setGeometry(20, 50, 160, 30);

  editPointSeparation = new QLineEdit(this);
  CHECK_PTR_ENGAUGE(editPointSeparation);
  editPointSeparation->setGeometry(190, 50, 130, 30);
  editPointSeparation->setText(QString("%1").arg(settings->pointSeparation));
  QWhatsThis::add(editPointSeparation, QString(tr("Select a point separation in pixels.\n\n"
    "Successive points added to a segment will be separated by this number of pixels. "
    "If Fill Corners is enabled, then additional points will be inserted at corners so some points "
    "will be closer.\n\n"
    "This value has a lower limit")));
  validatorPointSeparation = new QIntValidator(editPointSeparation);
  CHECK_PTR_ENGAUGE(validatorPointSeparation);
  editPointSeparation->setValidator(validatorPointSeparation);
  connect(editPointSeparation, SIGNAL(textChanged(const QString &)), this, SLOT(slotPointSeparation(const QString &)));

  labelFillCorners = new QLabel(QString(tr("Fill Corners:")), this);
  CHECK_PTR_ENGAUGE(labelFillCorners);
  labelFillCorners->setGeometry(20, 90, 160, 30);
  
  checkFillCorners = new QCheckBox(this);
  CHECK_PTR_ENGAUGE(checkFillCorners);
  checkFillCorners->setGeometry(190, 90, 130, 30);
  checkFillCorners->setChecked(settings->fillCorners);
  QWhatsThis::add(checkFillCorners, QString(tr("Fill corners.\n\n"
    "In addition to the points placed at regular intervals, this option causes a point to be "
    "placed at each corner. This option can capture important information in piecewise linear graphs, "
    "but gradually curving graphs may not benefit from the additional points")));
  connect(checkFillCorners, SIGNAL(toggled(bool)), this, SLOT(slotFillCorners(bool)));
  
  labelLineSize = new QLabel(QString(tr("Line Size:")), this);
  CHECK_PTR_ENGAUGE(labelLineSize);
  labelLineSize->setGeometry(20, 130, 160, 30);

  comboLineSize = new QComboBox(false, this, tr("Line Size"));
  CHECK_PTR_ENGAUGE(comboLineSize);
  comboLineSize->setGeometry(190, 130, 130, 30);
  comboLineSize->setEditable(false);
  comboLineSize->insertStringList(PointSetStyles::instance().lineSizeNames());
  QWhatsThis::add(comboLineSize, QString(tr("Select a size for the lines drawn along a segment")));
  connect(comboLineSize, SIGNAL(activated(const QString &)), this, SLOT(slotLineSize(const QString &)));
  connect(comboLineSize, SIGNAL(textChanged(const QString &)), this, SLOT(slotLineSize(const QString &)));

  labelLineColor = new QLabel(QString(tr("Line Color:")), this);
  CHECK_PTR_ENGAUGE(labelLineColor);
  labelLineColor->setGeometry(20, 170, 160, 30);

  comboLineColor = new QComboBox(false, this, tr("Line Color"));
  CHECK_PTR_ENGAUGE(comboLineColor);
  comboLineColor->setGeometry(190, 170, 130, 30);
  comboLineColor->setEditable(false);
  comboLineColor->insertStringList(PointSetStyles::instance().colorNames());
  QWhatsThis::add(comboLineColor, QString(tr("Select a color for the lines drawn along a segment")));
  connect(comboLineColor, SIGNAL(activated(const QString &)), this, SLOT(slotLineColor(const QString &)));

  // preview area
  labelPreview = new QLabel(QString(tr("Preview")), this);
  CHECK_PTR_ENGAUGE(labelPreview);
  labelPreview->setGeometry(10, 210, 160, 20);

  previewCanvas = new Q3Canvas(this);
  CHECK_PTR_ENGAUGE(previewCanvas);
  previewCanvas->resize(320, 100);
  QPixmap previewPixmap(segmentpreview_xpm);
  previewImageOriginal = previewPixmap.createHeuristicMask().convertToImage();
  
  previewCanvasView = new Q3CanvasView(previewCanvas, this);
  CHECK_PTR_ENGAUGE(previewCanvasView);
  previewCanvasView->setGeometry(10, 230, 320, 100);
  previewCanvasView->setHScrollBarMode(Q3ScrollView::AlwaysOff);
  previewCanvasView->setVScrollBarMode(Q3ScrollView::AlwaysOff);
  QWhatsThis::add(previewCanvasView, QString(tr("Preview window shows the shortest line that can be segment filled, "
    "and the effects of current settings on segments and points generated by segment fill")));

  segments = new Segments(previewCanvas);
  CHECK_PTR_ENGAUGE(segments);

  // navigation buttons
  buttonOk = new QPushButton(tr("OK"), this);
  CHECK_PTR_ENGAUGE(buttonOk);
  buttonOk->setGeometry(10, 340, 100, 30);
  connect(buttonOk, SIGNAL(clicked()), this, SLOT(accept()));

  buttonCancel = new QPushButton(tr("Cancel"), this);
  CHECK_PTR_ENGAUGE(buttonCancel);
  buttonCancel->setGeometry(140, 340, 100, 30);
  connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));

  buttonWhat = new QPushButton(this);
  CHECK_PTR_ENGAUGE(buttonWhat);
  buttonWhat->setPixmap(QPixmap(whatsthis_xpm));
  buttonWhat->setGeometry(270, 340, 60, 30);
  QToolTip::add(buttonWhat, QString(tr("What's this?")));
  connect(buttonWhat, SIGNAL(clicked()), this, SLOT(slotWhat()));

  // pointSet will own the preview points
  PointSetStyle style = DefaultSettings::instance().getCurveStyle(0);
  style.lineColor = DigitTransparent; // hide lines
  pointSet.setStyle(style);
  
  toggleActions();

  connect(this, SIGNAL(updatePreview()), this, SLOT(slotUpdatePreview()));
  emit(updatePreview());
}

SegmentDlg::~SegmentDlg()
{
  DigitDebug::dtor(QString("segmentdlg ") + QString::number((ulong) this, 16));

  if (segments)
  {
    delete segments;
    segments = 0;
  }

  if (previewCanvas)
  {
    delete previewCanvas;
    previewCanvas = 0;
  }
}

void SegmentDlg::toggleActions()
{
  ASSERT_ENGAUGE(comboLineSize != 0);
  comboLineSize->setCurrentText(PointSetStyles::instance().lineSizeName(settings->lineSize));
  ASSERT_ENGAUGE(comboLineColor != 0);
  comboLineColor->setCurrentText(PointSetStyles::instance().colorName(settings->lineColor));

  ASSERT_ENGAUGE(buttonOk != 0);
  buttonOk->setEnabled(validateSettings());
}

bool SegmentDlg::validateSettings()
{
  // enforce constraints
  ASSERT_ENGAUGE(settings != 0);
  if (settings->minPoints < DefaultSettings::instance().getSegmentSettings().minPoints)
    return false;
  if (settings->pointSeparation < DefaultSettings::instance().getSegmentPointMinSeparation())
    return false;

  return true;
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void SegmentDlg::slotFillCorners(bool check)
{
  ASSERT_ENGAUGE(settings != 0);
  settings->fillCorners = check;
  emit(updatePreview());
}

void SegmentDlg::slotLineSize(const QString &text)
{
  ASSERT_ENGAUGE(settings != 0);
  settings->lineSize = PointSetStyles::instance().lineSize(text);
  emit(updatePreview());
}

void SegmentDlg::slotLineColor(const QString &text)
{
  ASSERT_ENGAUGE(settings != 0);
  settings->lineColor = PointSetStyles::instance().color(text);
  emit(updatePreview());
}

void SegmentDlg::slotMinPoints(const QString &text)
{
  ASSERT_ENGAUGE(settings != 0);
  if (text == QString(""))
    settings->minPoints = 0;
  else
    settings->minPoints = text.toInt();
  toggleActions();
  emit(updatePreview());
}

void SegmentDlg::slotPointSeparation(const QString &text)
{
  ASSERT_ENGAUGE(settings != 0);
  if (text == QString(""))
    settings->pointSeparation = 0;
  else
    settings->pointSeparation = text.toInt();
  toggleActions();
  emit(updatePreview());
}

void SegmentDlg::slotUpdatePreview()
{
  // draw shortest horizontal line, 2 pixels wide, that will show minimum points and separation
  const int Y_HORIZONTAL_LINE = 20;
  QImage previewImage = previewImageOriginal.copy();
  int width = (settings->minPoints - 1) * settings->pointSeparation + 1; // add extra pixel to prevent roundoff problems
  int indexBlack = previewImage.pixelIndex(0, 0); // subtle trick here! put black in top-left pixel so index is available
  int xStart = previewCanvas->width() / 2 - width / 2;
  if (xStart < 0)
    xStart = 0;
  int xStop = previewCanvas->width() / 2 + width / 2;
  if (xStop >= previewCanvas->width())
    xStop = previewCanvas->width() - 1;
  for (int x = xStart; x <= xStop; x++)
  {
    previewImage.setPixel(x, Y_HORIZONTAL_LINE, indexBlack);
    previewImage.setPixel(x, Y_HORIZONTAL_LINE + 1, indexBlack);
  }
  QPixmap previewPixmap;
  previewPixmap.convertFromImage(previewImage);
  previewCanvas->setBackgroundPixmap(previewPixmap);

  // make segments for display
  QList<QRect> updateRectList;
  ASSERT_ENGAUGE(settings != 0);
  segments->makeSegments(previewImage, *settings);
  segments->showSegments(true, *settings, &updateRectList);

  if (validateSettings())
  {
    // make points for display
    pointSet.removePoints(); // remove existing points
    QList<QPoint> list = segments->fillPoints(*settings);
    QList<QPoint>::iterator itr;
    for (itr = list.begin(); itr != list.end(); ++itr)
    {
      Point* p = new Point((*itr).x(), (*itr).y(), previewCanvas);
      CHECK_PTR_ENGAUGE(p);

      pointSet.addPoint(previewCanvas, p, &updateRectList);
    }
  }
  else
    pointSet.removePoints();

  pointSet.show();

  previewCanvasView->repaintContents();
}

void SegmentDlg::slotWhat()
{
  QWhatsThis::enterWhatsThisMode();
}
