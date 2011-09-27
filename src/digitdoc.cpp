/***************************************************************************
                          digitdoc.cpp  -  description
                             -------------------
    begin                : Tue Oct 29 14:43:44 PST 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: digitdoc.cpp,v $
    Revision 1.14  2008/05/04 16:14:41  tsrsf
    update to reflect lastest Debian package
    change outside /debian/ allow compiling without qt 3 compat headers

    Revision 1.13  2007/04/09 07:13:40  markmitch
    Arrow keys move selection

    Revision 1.12  2007/01/03 01:54:13  markmitch
    Processing... dialog that required multithreading

    Revision 1.11  2006/12/26 09:03:09  markmitch
    Control click and drag in select mode

    Revision 1.10  2006/12/20 08:20:25  markmitch
    Rework of point matching to handle skipping

    Revision 1.9  2006/12/13 08:32:17  markmitch
    Fast convolution point match works, with build issues still

    Revision 1.8  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.6  2006/09/29 03:53:20  markmitch
    Version 3 commit with backwards compatibility

    Revision 1.3.2.5  2006/09/24 06:07:14  markmitch
    New date/time converter

    Revision 1.3.2.4  2006/09/13 06:17:02  markmitch
    Polar plot with origin offset works. Invalid axis/scale point combos prevented

    Revision 1.3.2.3  2006/09/08 07:03:36  markmitch
    Nonzero origin radius. Bugs: Not serialized, maybe nonzero+log issue

    Revision 1.3.2.2  2006/03/07 06:13:45  markmitch
    Version 2.14. Help window buttons visible. Lazy segment scanning

    Revision 1.3.2.1  2006/03/03 07:06:00  markmitch
    New NO_UNDO branch. Gcc 4 changes for Ubuntu. No more invoke

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.109  2004/11/18 05:40:45  markmitch
    Adjust precision of exported results to show significant digits

    Revision 1.108  2004/11/13 04:23:37  markmitch
    Sun Forte changes

    Revision 1.107  2004/10/29 03:06:13  markmitch
    Scan for axes works up to generating axis points

    Revision 1.106  2004/10/28 04:54:31  markmitch
    Scan for axes

    Revision 1.105  2004/10/19 06:58:38  markmitch
    View point selection handled same as background selection

    Revision 1.104  2004/10/18 23:00:54  markmitch
    Version numbers are now strings since 2.1 is not 2.10. Fixed displaying wrong points with multiple documents

    Revision 1.103  2004/10/07 07:55:47  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.102  2004/10/01 16:09:26  markmitch
    Document no longer handles saving on close

    Revision 1.101  2004/09/30 05:57:57  markmitch
    Fix file save on close. Better context sensitive help

    Revision 1.100  2004/09/27 07:14:54  markmitch
    Fix punctuation in critical messages

    Revision 1.99  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.97  2004/09/21 03:37:45  markmitch
    Icons for export menu items

    Revision 1.96  2004/09/18 14:46:32  markmitch
    Background outside of image is left gray

    Revision 1.95  2004/09/16 03:13:52  markmitch
    Document all new features. Paste works i Windows

    Revision 1.94  2004/09/15 04:43:28  markmitch
    Drag export geometry. Drag import image

    Revision 1.93  2004/09/13 08:32:31  markmitch
    Table-based geometry windows

    Revision 1.92  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.91  2004/09/12 04:52:14  markmitch
    Most settings are saved. Command line usage in Windows

    Revision 1.90  2004/09/11 05:59:17  markmitch
    First phase of settings archival

    Revision 1.89  2004/09/09 05:33:44  markmitch
    Invoker in work. Windows upgrade to 3.3.3

    Revision 1.88  2004/04/30 22:29:55  markmitch
    Skip saving when no points matched

    Revision 1.87  2004/04/22 04:57:45  markmitch
    Robust log calls

    Revision 1.86  2004/03/18 16:55:23  markmitch
    Can read bmp files in Simplified Chinese Windows

    Revision 1.85  2004/02/03 01:43:22  markmitch
    Saved files corrupted in Windows. Magic number

    Revision 1.84  2004/01/31 18:35:10  markmitch
    Saving match points

    Revision 1.83  2004/01/29 07:02:59  markmitch
    Output file extension is csv

    Revision 1.82  2004/01/25 19:06:58  markmitch
    Version 2.1. Limited recursion. Default grid removal settings

    Revision 1.81  2004/01/20 03:45:13  markmitch
    Warning if zero points matched

    Revision 1.80  2004/01/19 17:56:31  markmitch
    Combobox focus. Point match style. Empty accepted list

    Revision 1.79  2004/01/17 04:05:11  markmitch
    Segment Fill fix for Windows

    Revision 1.78  2004/01/15 08:24:48  markmitch
    Delete keypress. Documentation

    Revision 1.77  2004/01/14 06:54:37  markmitch
    Point match works well and has documentation

    Revision 1.76  2004/01/13 18:53:33  markmitch
    Point match works but needs bells and whistles

    Revision 1.75  2004/01/13 17:54:06  markmitch
    Testing point match

    Revision 1.74  2004/01/08 06:48:35  markmitch
    Reworked menu icons look great

    Revision 1.73  2004/01/07 07:48:07  markmitch
    Implementing point match

    Revision 1.72  2004/01/06 08:14:39  markmitch
    Point match mode highlights sample point

    Revision 1.71  2004/01/04 08:40:59  markmitch
    Dialog for point match settings

    Revision 1.70  2004/01/01 22:15:04  markmitch
    Delete key deletes. No no-op Cancel buttons. No crash from Divider click

    Revision 1.69  2004/01/01 03:52:40  markmitch
    Document stores QImage for speed

    Revision 1.68  2003/12/31 06:19:19  markmitch
    Grid removal option is saved

    Revision 1.67  2003/12/30 09:14:32  markmitch
    Color chooser has two formats and can be disabled

    Revision 1.66  2003/12/29 20:51:50  markmitch
    All discretize modes work

    Revision 1.65  2003/12/29 06:55:10  markmitch
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

#ifdef _MSC_VER
// use pragma to prevent useless warning from Microsoft compiler
#pragma warning ( disable : 4355 )  // 'this' used in base init list
#endif

#include <qdir.h>
#include <qfileinfo.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qprinter.h>
#include <qpainter.h>
//Added by qt3to4:
#include <QPixmap>
#include <Q3ValueList>
#include <Q3TextStream>
#include <Q3PtrList>
#include <QPolygon>


#include <math.h>

#include "digitdoc.h"
#include "digitmain.h"
#include "digitview.h"
#include "pointsets.h"
#include "segment.h"
#include "segments.h"
#include "mmsubs.h"
#include "transform.h"
#include "grid.h"
#include "digitdebug.h"
#include "clipboard.h"
#include "main.h"
#include "discretize.h"
#include "gridremoval.h"
#include "pointmatch.h"
#include "match.h"
#include "matchset.h"
#include "scanforaxes.h"
#include "defaultsettings.h"

extern bool cmdLazySegments;
extern bool cmdOnlyBmp;
extern bool cmdPixels;

DigitDoc::DigitDoc(DigitizeState state) :
  m_savePath(QString("")),
  m_exportPath(QString("")),
  m_exportFileExists(false),
  m_viewPointSelection(ViewAllPoints),
  m_inViewPointSelectionOverride(false),
  m_backgroundSelection(ProcessedImage),
  m_canvas(this),
  m_digitizeState(state),
  m_dirtyAxesTransformation(true),
  m_dirtyScaleTransformation(true),
  m_samplePointPixels(0)
{
  DigitDebug::ctor(QString("digitdoc ") + QString::number((ulong) this, 16));
  
  // make sure the application version number has been added to list of supported version numbers
  ASSERT_ENGAUGE(supportedVersionNumber(VersionNumber));

  // disallow SegmentState when lazy segment scanning is in effect
  if (cmdLazySegments && (m_digitizeState == SegmentState))
  {
     state = AxisState; // pick any state other than SegmentState
     m_digitizeState = state;
  }
  
  m_viewList = new Q3PtrList<DigitView>;
  CHECK_PTR_ENGAUGE(m_viewList);
  m_viewList->setAutoDelete(true);

  m_pointSets = new PointSets;
  CHECK_PTR_ENGAUGE(m_pointSets);
  m_segments = new Segments(canvas());
  CHECK_PTR_ENGAUGE(m_segments);
  m_matchSet = new MatchSet();
  CHECK_PTR_ENGAUGE(m_matchSet);
  m_transform = new Transform(this);
  CHECK_PTR_ENGAUGE(m_transform);
  m_gridDisplay = new Grid(GridTypeDisplay, canvas());
  CHECK_PTR_ENGAUGE(m_gridDisplay);

  DefaultSettings& rSettings = DefaultSettings::instance();

  m_coordSettings = rSettings.getCoordSettings();

  m_exportSettings = rSettings.getExportSettings();

  // do not initialize grid line settings structures m_gridRemovalSettings and
  // m_gridSettings. user will not be allowed to configure the grid line settings
  // until after the transformation is defined, since:
  // (1) user will then have useful default values to work with
  // (2) grid display lines cannot even be converted to screen coordinates for
  //     display until the transformation is defined

  m_segmentSettings = rSettings.getSegmentSettings();

  m_pointMatchSettings = rSettings.getPointMatchSettings();
  
  m_gridRemovalSettings = rSettings.getGridRemovalSettings();

  m_gridDisplaySettings.initialized = false;
  m_gridDisplaySettings.gridSetX = rSettings.getGridDisplayGridSetX();
  m_gridDisplaySettings.gridSetY = rSettings.getGridDisplayGridSetY();

  m_discretizeSettings = rSettings.getDiscretizeSettings();
}

DigitDoc::~DigitDoc()
{
  DigitDebug::dtor(QString("digitdoc ") + QString::number((ulong) this, 16));
  
  delete m_viewList; // autoDelete is on

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->deleteShared();
  delete m_pointSets;
  delete m_segments;
  delete m_matchSet;
  delete m_transform;
  delete m_gridDisplay;
}

void DigitDoc::initDefaults()
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->addCurve(DefaultCurveName);
  m_pointSets->addMeasure(DefaultMeasureName);

  m_curveCmbText = DefaultCurveName;
  m_measureCmbText = DefaultMeasureName;
}

void DigitDoc::addView(DigitView* view)
{
  setViewCursor(view);
  ASSERT_ENGAUGE(m_viewList != 0);
  m_viewList->append(view);
  changedViewList();
}

void DigitDoc::removeView(DigitView* view)
{
  ASSERT_ENGAUGE(m_viewList != 0);
  m_viewList->remove(view);
  if (!m_viewList->isEmpty())
    changedViewList();
}

void DigitDoc::changedViewList(){

  DigitView* view;
  if (isLastView())
  {
    view = m_viewList->first();
    view->setCaption(tr(m_title));
  }
  else
  {
    int i;
    for (i = 1, view = m_viewList->first(); view != 0; i++, view = m_viewList->next())
      view->setCaption(tr(m_title + ":%1").arg(i));
  }
}

bool DigitDoc::isLastView()
{
  ASSERT_ENGAUGE(m_viewList != 0);
  return ((int) m_viewList->count() == 1);
}

void DigitDoc::setViewCursor(DigitView* view)
{
  // TODO allow different cursors
  ASSERT_ENGAUGE(view != 0);
  switch (m_digitizeState)
  {
    case PointMatchState:
    case SelectState:
    case SegmentState:
      view->setCursor(Qt::ArrowCursor);
      break;
    case AxisState:
    case CurveState:
    case MeasureState:
    case ScaleState:
      view->setCursor(Qt::CrossCursor);
      break;
  }
}

void DigitDoc::setSavePath(const QString &filename)
{
  QFileInfo fInfo(filename);

  m_savePath = fInfo.dirPath(true) + QDir::separator() + fInfo.baseName(true) + extensionDig;
  m_title = fInfo.baseName();

  if (m_exportPath.isEmpty())
    m_exportPath = fInfo.dirPath(true) + QDir::separator() + fInfo.baseName(true) + extensionCsv;
}

void DigitDoc::setExportPath(const QString &filename)
{
  QFileInfo fInfo(filename);

  m_exportPath = fInfo.dirPath(true) + QDir::separator() + fInfo.baseName(true) + extensionCsv;

  if (m_savePath.isEmpty())
  {
    m_savePath = fInfo.dirPath(true) + QDir::separator() + fInfo.baseName(true) + extensionDig;
    m_title = fInfo.baseName();
  }
}

bool DigitDoc::importFile(const QString &filename, const char* format)
{
  static char formatBmp [] = "BMP";
  const char* formatUsed;
  if (cmdOnlyBmp)
    formatUsed = formatBmp;
  else
    formatUsed = format;
    
  if (!m_originalPixmap.load (filename, formatUsed,
    Qt::ThresholdDither | Qt::ThresholdAlphaDither | Qt::AvoidDither))
  {
    return false;
  }
  
  loadOriginalPixmap();
  processOriginalPixmap();

  // isolate background color as useful default for grid removal by color
  Discretize discretize;
  QRgb rgbBg = discretize.backgroundColor(&m_originalImage);
  m_gridRemovalSettings.color = rgbBg;

  m_modified = false;
  m_saveFileExists = false;
  setSavePath(filename);
  return true;
}

bool DigitDoc::importImage(const QImage& image)
{
  if (!m_originalPixmap.convertFromImage (image,
    Qt::ThresholdDither | Qt::ThresholdAlphaDither | Qt::AvoidDither))
  {
    return false;
  }

  loadOriginalPixmap();
  processOriginalPixmap();

  // isolate background color as useful default for grid removal by color
  Discretize discretize;
  QRgb rgbBg = discretize.backgroundColor(&m_originalImage);
  m_gridRemovalSettings.color = rgbBg;

  m_modified = false;
  m_saveFileExists = false;
  return true;
}

bool DigitDoc::importPixmap(const QPixmap& pixmap)
{
  m_originalPixmap = pixmap;

  loadOriginalPixmap();
  processOriginalPixmap();

  // isolate background color as useful default for grid removal by color
  Discretize discretize;
  QRgb rgbBg = discretize.backgroundColor(&m_originalImage);
  m_gridRemovalSettings.color = rgbBg;

  m_modified = false;
  m_saveFileExists = false;
  return true;
}

void DigitDoc::loadOriginalPixmap()
{
  m_originalImage = m_originalPixmap.convertToImage();

  m_canvas.setBackgroundPixmap(m_originalPixmap);
}

void DigitDoc::processOriginalPixmap()
{
  // make sure canvas has the correct size
  if (m_canvas.size() != m_originalPixmap.size())
    m_canvas.resize (m_originalPixmap.width(), m_originalPixmap.height());

  // processing involves two steps
  // 1) remove gridlines
  // 2) discretize
  Discretize discretize;
  QRgb backgroundColor = discretize.backgroundColor(&m_originalImage);

  m_processedImage = m_originalImage.copy(); // deep copy needed

  GridRemoval gridRemoval;
  gridRemoval.removeAndConnect(&m_processedImage, m_transform, m_coordSettings,
    m_gridRemovalSettings, backgroundColor);

  discretize.discretize(&m_processedImage, m_discretizeSettings);

  if (!cmdLazySegments)
  {
     // make segments using processed image with gridlines removed
     ASSERT_ENGAUGE(m_segments != 0);
     m_segments->makeSegments(m_processedImage, segmentSettings());
     showSegments(m_digitizeState == SegmentState);
  }
  
  m_processedPixmap.convertFromImage(m_processedImage, Qt::ThresholdDither);
  
  if (m_backgroundSelection == ProcessedImage)
    m_canvas.setBackground(m_backgroundSelection);
}

bool DigitDoc::supportedVersionNumber(QString versionNumber)
{
  return (VersionNumbersSupported.contains(versionNumber) > 0);
}

bool DigitDoc::openDocument(const QString &filename)
{
  QFile f(filename);
  if (!f.open (QIODevice::ReadOnly))
    return false;

  QDataStream str (&f);

  Q_INT32 magicNumber;
  str >> (Q_INT32 &) magicNumber;

  if (magicNumber != MagicNumber)
  {
    QMessageBox::critical(0, tr("I/O Error!"), tr("Invalid file format!\n"
      "Skipping file"), QMessageBox::Ok, Qt::NoButton);
    f.close();
    return false;
  }

  double versionNumber;
  QString versionString;
  str >> versionNumber; // numeric value is ambiguous (2.1 or 2.10?)
  str >> versionString;
  if (versionString.isEmpty()) // kludge for files with empty version strings
    versionString = QString("%1").arg(versionNumber);
  if (!supportedVersionNumber(versionString))
  {
    QMessageBox::critical(0, tr("I/O Error!"), QString("%1%2%3")
      .arg(tr("Unsupported version "))
      .arg(versionString)
      .arg(tr("\nSkipping file")), QMessageBox::Ok, Qt::NoButton);
    f.close();
    return false;
  }

  str >> (Q_INT32 &) m_backgroundSelection;
  str >> m_originalPixmap;

  str >> m_title;

  str >> m_curveCmbText;
  str >> m_measureCmbText;

  str >> (Q_INT32 &) m_coordSettings.frame;
  if (versionNumber < 3)
     m_coordSettings.originRadius = 0.0;
  else
     str >> (double &) m_coordSettings.originRadius;
  str >> (Q_INT32 &) m_coordSettings.thetaUnits;
  str >> (Q_INT32 &) m_coordSettings.xThetaScale;
  str >> (Q_INT32 &) m_coordSettings.yRScale;

  str >> (Q_INT32 &) m_exportSettings.delimiters;
  str >> (Q_INT32 &) m_exportSettings.layout;
  str >> (Q_INT32 &) m_exportSettings.pointsSelection;
  str >> (Q_INT32 &) m_exportSettings.header;

  str >> (Q_INT32 &) m_gridRemovalSettings.removeThinLines;
  str >> (double &) m_gridRemovalSettings.thinThickness;
  str >> (Q_INT32 &) m_gridRemovalSettings.removeGridlines;
  str >> (Q_INT32 &) m_gridRemovalSettings.gridMesh.initialized;
  str >> (Q_INT32 &) m_gridRemovalSettings.gridMesh.countX;
  str >> (Q_INT32 &) m_gridRemovalSettings.gridMesh.countY;
  str >> (Q_INT32 &) m_gridRemovalSettings.gridMesh.gridSetX;
  str >> (Q_INT32 &) m_gridRemovalSettings.gridMesh.gridSetY;
  str >> (double &) m_gridRemovalSettings.gridMesh.startX;
  str >> (double &) m_gridRemovalSettings.gridMesh.startY;
  str >> (double &) m_gridRemovalSettings.gridMesh.stepX;
  str >> (double &) m_gridRemovalSettings.gridMesh.stepY;
  str >> (double &) m_gridRemovalSettings.gridMesh.stopX;
  str >> (double &) m_gridRemovalSettings.gridMesh.stopY;
  str >> (double &) m_gridRemovalSettings.gridDistance;
  str >> (Q_INT32 &) m_gridRemovalSettings.removeColor;
  str >> m_gridRemovalSettings.color;
  str >> (Q_INT32 &) m_gridRemovalSettings.foregroundThresholdLow;
  str >> (Q_INT32 &) m_gridRemovalSettings.foregroundThresholdHigh;
  str >> (double &) m_gridRemovalSettings.gapSeparation;

  str >> (Q_INT32 &) m_gridDisplaySettings.initialized;
  str >> (Q_INT32 &) m_gridDisplaySettings.countX;
  str >> (Q_INT32 &) m_gridDisplaySettings.countY;
  str >> (Q_INT32 &) m_gridDisplaySettings.gridSetX;
  str >> (Q_INT32 &) m_gridDisplaySettings.gridSetY;
  str >> (double &) m_gridDisplaySettings.startX;
  str >> (double &) m_gridDisplaySettings.startY;
  str >> (double &) m_gridDisplaySettings.stepX;
  str >> (double &) m_gridDisplaySettings.stepY;
  str >> (double &) m_gridDisplaySettings.stopX;
  str >> (double &) m_gridDisplaySettings.stopY;

  str >> (Q_INT32 &) m_segmentSettings.minPoints;
  str >> (Q_INT32 &) m_segmentSettings.pointSeparation;
  str >> (Q_INT32 &) m_segmentSettings.lineSize;
  str >> (Q_INT32 &) m_segmentSettings.lineColor;

  str >> (Q_INT32 &) m_pointMatchSettings.pointSeparation;
  str >> (Q_INT32 &) m_pointMatchSettings.pointSize;
  str >> (Q_INT32 &) m_pointMatchSettings.acceptedColor;
  str >> (Q_INT32 &) m_pointMatchSettings.rejectedColor;
  if (versionNumber < 4)
  {
    // synchronize with DefaultSettings::initializeSettingsToFactoryDefaults
    m_pointMatchSettings.candidateColor = DigitBlue;
  }
  else
    str >> (Q_INT32 &) m_pointMatchSettings.candidateColor;

  str >> (Q_INT32 &) m_discretizeSettings.discretizeMethod;
  str >> (Q_INT32 &) m_discretizeSettings.intensityThresholdLow;
  str >> (Q_INT32 &) m_discretizeSettings.intensityThresholdHigh;
  str >> (Q_INT32 &) m_discretizeSettings.foregroundThresholdLow;
  str >> (Q_INT32 &) m_discretizeSettings.foregroundThresholdHigh;
  str >> (Q_INT32 &) m_discretizeSettings.hueThresholdLow;
  str >> (Q_INT32 &) m_discretizeSettings.hueThresholdHigh;
  str >> (Q_INT32 &) m_discretizeSettings.saturationThresholdLow;
  str >> (Q_INT32 &) m_discretizeSettings.saturationThresholdHigh;
  str >> (Q_INT32 &) m_discretizeSettings.valueThresholdLow;
  str >> (Q_INT32 &) m_discretizeSettings.valueThresholdHigh;

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->serializeRead(str, canvas());

  str >> (Q_INT32 &) magicNumber;

  if (magicNumber != MagicNumber)
  {
    QMessageBox::critical(0, tr("I/O Error!"), tr("Invalid file format!\n"
    "Skipping file"), QMessageBox::Ok, Qt::NoButton);
    f.close();
    return false;
  }

  f.close();

  computeTransformation();

  // document has been read in so initialize
  m_modified = false;
  m_saveFileExists = true;
  setSavePath(filename);
  m_dirtyAxesTransformation = true;
  m_dirtyScaleTransformation = true;

  makeGridDisplayLines();

  loadOriginalPixmap();
  processOriginalPixmap();

  return true;
}

bool DigitDoc::saveDocument(const QString &filename)
{
  QFile f(filename);
  // translation flag applies to Microsoft Windows
  if (!f.open (QIODevice::WriteOnly))
    return false;

  QDataStream str (&f);

#ifdef __SUNPRO_CC
  str << (Q_INT32 &) MagicNumber;
#else
  str << (const Q_INT32 &) MagicNumber;
#endif

  str << VersionNumber.toDouble(); // numeric value is ambiguous (2.1 or 2.10?)
  str << VersionNumber;

  str << (Q_INT32 &) m_backgroundSelection;
  str << m_originalPixmap;

  str << m_title;

  str << m_curveCmbText;
  str << m_measureCmbText;

  str << (Q_INT32 &) m_coordSettings.frame;
  str << (double &) m_coordSettings.originRadius;
  str << (Q_INT32 &) m_coordSettings.thetaUnits;
  str << (Q_INT32 &) m_coordSettings.xThetaScale;
  str << (Q_INT32 &) m_coordSettings.yRScale;

  str << (Q_INT32 &) m_exportSettings.delimiters;
  str << (Q_INT32 &) m_exportSettings.layout;
  str << (Q_INT32 &) m_exportSettings.pointsSelection;
  str << (Q_INT32 &) m_exportSettings.header;

  str << (Q_INT32 &) m_gridRemovalSettings.removeThinLines;
  str << (double &) m_gridRemovalSettings.thinThickness;
  str << (Q_INT32 &) m_gridRemovalSettings.removeGridlines;
  str << (Q_INT32 &) m_gridRemovalSettings.gridMesh.initialized;
  str << (Q_INT32 &) m_gridRemovalSettings.gridMesh.countX;
  str << (Q_INT32 &) m_gridRemovalSettings.gridMesh.countY;
  str << (Q_INT32 &) m_gridRemovalSettings.gridMesh.gridSetX;
  str << (Q_INT32 &) m_gridRemovalSettings.gridMesh.gridSetY;
  str << (double &) m_gridRemovalSettings.gridMesh.startX;
  str << (double &) m_gridRemovalSettings.gridMesh.startY;
  str << (double &) m_gridRemovalSettings.gridMesh.stepX;
  str << (double &) m_gridRemovalSettings.gridMesh.stepY;
  str << (double &) m_gridRemovalSettings.gridMesh.stopX;
  str << (double &) m_gridRemovalSettings.gridMesh.stopY;
  str << (double &) m_gridRemovalSettings.gridDistance;
  str << (Q_INT32 &) m_gridRemovalSettings.removeColor;
  str << m_gridRemovalSettings.color;
  str << (Q_INT32 &) m_gridRemovalSettings.foregroundThresholdLow;
  str << (Q_INT32 &) m_gridRemovalSettings.foregroundThresholdHigh;
  str << (double &) m_gridRemovalSettings.gapSeparation;

  str << (Q_INT32 &) m_gridDisplaySettings.initialized;
  str << (Q_INT32 &) m_gridDisplaySettings.countX;
  str << (Q_INT32 &) m_gridDisplaySettings.countY;
  str << (Q_INT32 &) m_gridDisplaySettings.gridSetX;
  str << (Q_INT32 &) m_gridDisplaySettings.gridSetY;
  str << (double &) m_gridDisplaySettings.startX;
  str << (double &) m_gridDisplaySettings.startY;
  str << (double &) m_gridDisplaySettings.stepX;
  str << (double &) m_gridDisplaySettings.stepY;
  str << (double &) m_gridDisplaySettings.stopX;
  str << (double &) m_gridDisplaySettings.stopY;

  str << (Q_INT32 &) m_segmentSettings.minPoints;
  str << (Q_INT32 &) m_segmentSettings.pointSeparation;
  str << (Q_INT32 &) m_segmentSettings.lineSize;
  str << (Q_INT32 &) m_segmentSettings.lineColor;

  str << (Q_INT32 &) m_pointMatchSettings.pointSeparation;
  str << (Q_INT32 &) m_pointMatchSettings.pointSize;
  str << (Q_INT32 &) m_pointMatchSettings.acceptedColor;
  str << (Q_INT32 &) m_pointMatchSettings.rejectedColor;
  str << (Q_INT32 &) m_pointMatchSettings.candidateColor;
    
  str << (Q_INT32 &) m_discretizeSettings.discretizeMethod;
  str << (Q_INT32 &) m_discretizeSettings.intensityThresholdLow;
  str << (Q_INT32 &) m_discretizeSettings.intensityThresholdHigh;
  str << (Q_INT32 &) m_discretizeSettings.foregroundThresholdLow;
  str << (Q_INT32 &) m_discretizeSettings.foregroundThresholdHigh;
  str << (Q_INT32 &) m_discretizeSettings.hueThresholdLow;
  str << (Q_INT32 &) m_discretizeSettings.hueThresholdHigh;
  str << (Q_INT32 &) m_discretizeSettings.saturationThresholdLow;
  str << (Q_INT32 &) m_discretizeSettings.saturationThresholdHigh;
  str << (Q_INT32 &) m_discretizeSettings.valueThresholdLow;
  str << (Q_INT32 &) m_discretizeSettings.valueThresholdHigh;

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->serializeWrite(str);

#ifdef __SUNPRO_CC
  str << (Q_INT32 &) MagicNumber;
#else
  str << (const Q_INT32 &) MagicNumber;
#endif

  f.close();

  m_modified = false;
  m_saveFileExists = true;
  setSavePath(filename);
  return true;
}

bool DigitDoc::exportDocument(const QString &filename)
{
  QFile file(filename);

  if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    return false;

  Q3TextStream str(&file);

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->exportToStream(str, coordSettings(), gridDisplaySettings(), exportSettings());

  file.close();

  setExportPath(filename);

  return true;
}

bool DigitDoc::isActionToUndo()
{
  return true;
}

bool DigitDoc::isActionToRedo()
{
  return true;
}

void DigitDoc::undo()
{
}

void DigitDoc::redo()
{
}

void DigitDoc::cut(DigitView* view)
{
  m_modified = true;

  bool needNewTransform = false;

  // remove items selected in the view from the document, and send their attributes to the clipboard
  Clipboard::instance().clear();

  Q3ValueList<QRect> updateRectList;
  Q3CanvasItemList::iterator itr;
  ASSERT_ENGAUGE(view != 0);
  for (itr = view->selectionList.begin(); itr != view->selectionList.end(); ++itr)
  {
    Point* p = view->safeUpcast(itr);
    if (p != 0)
    {
      Clipboard::instance().addPoint(p->xScreen(), p->yScreen());

      ASSERT_ENGAUGE(m_pointSets != 0);
      if (m_pointSets->removePoint(p, &updateRectList))
        needNewTransform = true;
    }
  }

  view->unselect();

  if (needNewTransform)
  {
     // needNewTransform was set true by the removal of one or more axis or scale points
    m_dirtyAxesTransformation = true;
    m_dirtyScaleTransformation = true;

    computeTransformation();
  }

  // update all views
  updateFromList(&updateRectList);

  sendUpdateGeometry();
}

void DigitDoc::copy(DigitView* view)
{
  // copy items selected in the view to the clipboard
  Clipboard::instance().clear();

  Q3CanvasItemList::iterator itr;
  ASSERT_ENGAUGE(view != 0);
  for (itr = view->selectionList.begin(); itr != view->selectionList.end(); ++itr)
  {
    Point* p = view->safeUpcast(itr);
    if (p != 0)
    {
      ASSERT_ENGAUGE(p != 0);
      Clipboard::instance().addPoint(p->xScreen(), p->yScreen());
    }
  }

  sendUpdateGeometry();
}

void DigitDoc::paste(DigitView* view)
{
  m_modified = true;

  Q3CanvasItemList newSelection;

  // paste points into document
  Q3ValueList<QPoint>* list = Clipboard::instance().contents();
  Q3ValueList<QPoint>::iterator itr;

  ASSERT_ENGAUGE(list != 0);
  for (itr = list->begin(); itr != list->end(); ++itr)
  {
    int xScreen = (*itr).x();
    int yScreen = (*itr).y();

    Point* p = addPoint(xScreen, yScreen);

    newSelection.append((Q3CanvasItem*) p);
  }

  // replace any existing selection by new points
  ASSERT_ENGAUGE(view != 0);
  view->selectItemsReplace(&newSelection);

  sendUpdateGeometry();
}

void DigitDoc::curveNames(QStringList* list)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->curveNames(list);
}

void DigitDoc::measureNames(QStringList* list)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->measureNames(list);
}

void DigitDoc::replacePointSets(PointSets* pointsets,
  QStringList* curvesWithOrphanedPoints,
  QStringList* measuresWithOrphanedPoints)
{
  m_modified = true;

  ASSERT_ENGAUGE(m_pointSets != 0);
  if (curvesWithOrphanedPoints)
    m_pointSets->removePointsForSelectedCurves(curvesWithOrphanedPoints);

  if (measuresWithOrphanedPoints)
    m_pointSets->removePointsForSelectedMeasures(measuresWithOrphanedPoints);

  delete m_pointSets;
  m_pointSets = pointsets;

  m_pointSets->attachPointsToPointSets();

  // update all views so all points reflect the style of the associated pointset,
  // and lines appear
  slotUpdateViews(0, m_canvas.rect());

  QStringList names;

  // if m_curveCmbText is not found in the new list of curves, then arbitrarily pick
  // first curve. a popup will be generated elsewhere so user will realize this occurred
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->curveNames(&names);
  if (names.find(m_curveCmbText) == names.end())
    m_curveCmbText = names.first();

  // if m_measureCmbText is not found in the new list of measures, then arbitrarily pick
  // first measure. a popup will be generated elsewhere so user will realize this occurred
  m_pointSets->measureNames(&names);
  if (names.find(m_measureCmbText) == names.end())
    m_measureCmbText = names.first();
}

void DigitDoc::forwardNormalMsg(QString message)
{
  emit(normalMsg(message));
}

void DigitDoc::forwardPermanentMsg(QString message)
{
  emit(permanentMsg(message));
}

void DigitDoc::screenToXThetaYR(int xScreen, int yScreen, double* xTheta, double* yR)
{
  ASSERT_ENGAUGE(m_transform != 0);
  m_transform->screenToXThetaYR(m_coordSettings, xScreen, yScreen, xTheta, yR);
}

void DigitDoc::trackCursor(const QPoint &p)
{
  ASSERT_ENGAUGE(m_transform != 0);
  if (cmdPixels || m_transform->validAxes() || m_transform->validScale())
  {
    QString textCoords, textRes;

    if (cmdPixels)
    {
      // display raw pixel coordinates for debugging segments, zoom, etc.
      textCoords.sprintf("(%d, %d)", p.x(), p.y());
      textRes.sprintf("(1, 1)");
    }
    else
    {
      // compute graph coordinates from original screen coordinates, without and with differentials
      double xTheta, yR, xThetaTweakX, yRTweakX, xThetaTweakY, yRTweakY;
      screenToXThetaYR(p.x(), p.y(), &xTheta, &yR);
      screenToXThetaYR(p.x() + 1, p.y(), &xThetaTweakX, &yRTweakX);
      screenToXThetaYR(p.x(), p.y() + 1, &xThetaTweakY, &yRTweakY);

      // compute resolution in each direction
      double xThetaResX = dabs(xTheta - xThetaTweakX);
      double yRResX = dabs(yR - yRTweakX);

      double xThetaResY = dabs(xTheta - xThetaTweakY);
      double yRResY = dabs(yR - yRTweakY);

      // combine the resolutions in each direction using root-mean-squared. the rationale is
      // that if the graph was exactly aligned in the horizontal and vertical screen directions,
      // the rms values xThetaRes and yRRes would obviously equal xThetaResX and yRResY respectively,
      // as desired. however, the irritation with this approach is that the coordinates of
      // a slightly rotated graph will not show the coupling of the x and y values, since
      // going up on the screen will cause changes in the least significant digits of
      // the x coordinate. the same is true for going right with the y coordinate. these slight
      // changes will be hidden by the roundoff step, but this is acceptable since we prefer the
      // cleaner look of a rounded off value in the statusbar. note the full precision will show
      // up in the exported files
      //
      // there is another argument for using the rms approach which hides slight coupling of
      // slightly rotated graphs. if the resolution in the x direction, which is limited by the
      // pixel spacing, is some value, it does not make sense to show much smaller contributions
      // due to the vertical coupling. in other words, we would be fine tuning a coarse value.
      double xThetaRes = sqrt(xThetaResX * xThetaResX + xThetaResY * xThetaResY);
      double yRRes = sqrt(yRResX * yRResX + yRResY * yRResY);

      // most significant digits
      int powerMostSigX = valuePower(xTheta) - 1;
      int powerMostSigY = valuePower(yRRes) - 1;

      // pick least significant digit that gives arbitrary two significant digits in
      // resolution. example: use 0.001 for 0.03
      int powerLeastSigX = valuePower(xThetaRes) - 1;
      int powerLeastSigY = valuePower(yRRes) - 1;

      // build format string on the fly since we need a constant precision. otherwise, while moving
      // the cursor around trailing zeros would be dropped sometimes, causing the field width to
      // vary often, which causes the statusbar widgets to shift around. this is highly irritating.
      // default format is fixed, with precision set by least significant digits
      QString xFormat("%.*f");
      QString yFormat("%.*f");
      int precisionX = -powerLeastSigX;
      int precisionY = -powerLeastSigY;
      double roundedX = roundofftopower(xTheta, powerLeastSigX);
      double roundedY = roundofftopower(yR, powerLeastSigY);
      double roundedXRes = roundofftopower(xThetaRes, powerLeastSigX);
      double roundedYRes = roundofftopower(yRRes, powerLeastSigY);

      if ((powerMostSigX > DefaultSettings::instance().getPowerMostSigMax()) ||
        (DefaultSettings::instance().getPowerMostSigMin() > powerMostSigX))
      {
        ASSERT_ENGAUGE(m_canvas.width() > 1);
        precisionX = (int) (1 + log10(m_canvas.width()));
        roundedX = xTheta;
        roundedXRes = xThetaRes;
        xFormat = "%.*e"; // use e since g does not have trailing zeros, causing flicker during mouse moves
      }
      if ((powerMostSigY > DefaultSettings::instance().getPowerMostSigMax()) ||
        (DefaultSettings::instance().getPowerMostSigMin() > powerMostSigY))
      {
        ASSERT_ENGAUGE(m_canvas.height() > 1);
        precisionY = (int) (1 + log10(m_canvas.height()));
        roundedY = yR;
        roundedYRes = yRRes;
        yFormat = "%.*e"; // use e since g does not have trailing zeros, causing flicker during mouse moves
      }

      QString xyFormat = QString("(") + xFormat + QString(",") + yFormat + QString(")");

      textCoords.sprintf(xyFormat,
        precisionX, roundedX,
        precisionY, roundedY);
      textRes.sprintf(xyFormat,
        precisionX, roundedXRes,
        precisionY, roundedYRes);
    }

    if (!cmdPixels && !m_transform->validAxes())
    {
      // if using scale bar, then coordinates are arbitrary so do not display them
      textCoords = QString("");
    }

    emit(trackingMsg(textCoords, textRes));
  }
  else
    emit(trackingMsg(QString(""), QString("")));
}
            
void DigitDoc::setDigitizeState(DigitizeState state)
{
  // on state transitions, always turn off override
  stopShowOnlySelectedCurve();

  if ((m_digitizeState == PointMatchState) && (state != PointMatchState))
    cleanUpAcceptedPoints(state);

  if (cmdLazySegments && (state == SegmentState))
  {
     // no longer able to postpone lazy segment scanning
     cmdLazySegments = false;
     
     ASSERT_ENGAUGE(m_segments != 0);
     m_segments->makeSegments(m_processedImage, segmentSettings());
  }
  
  m_digitizeState = state;

  // state transitions involving segment state require hiding or showing segments
  showSegments(m_digitizeState == SegmentState);
  
  DigitView* view;
  for(view = m_viewList->first(); view != 0; view = m_viewList->next())
    setViewCursor(view);
}

Point* DigitDoc::addPoint(int xScreen, int yScreen)
{
  m_modified = true;

  double xThetaGraph = 0.0, yRGraph = 0.0;

  // new canvas item object
  Point* p;

  if ((m_digitizeState == CurveState) ||
    (m_digitizeState == MeasureState))
  {
    screenToXThetaYR(xScreen, yScreen, &xThetaGraph, &yRGraph);

    p = new Point(xScreen, yScreen, xThetaGraph, yRGraph, &m_canvas);
    CHECK_PTR_ENGAUGE(p);
  }
  else {
    p = new Point(xScreen, yScreen, &m_canvas);
    CHECK_PTR_ENGAUGE(p);
  }

  Q3ValueList<QRect> updateRectList;

  ASSERT_ENGAUGE(m_pointSets != 0);
  switch (m_digitizeState)
  {
    case AxisState:
      m_dirtyAxesTransformation = true;
      m_pointSets->addPointAxes(&m_canvas, p, &updateRectList);
      break;
    case CurveState:
    case SegmentState:
      m_pointSets->addPointCurve(&m_canvas, p, m_curveCmbText, &updateRectList);
      break;
    case MeasureState:
      m_pointSets->addPointMeasure(&m_canvas, p, m_measureCmbText, &updateRectList);
      break;
    case ScaleState:
      m_dirtyScaleTransformation = true;
      m_pointSets->addPointScale(&m_canvas, p, &updateRectList);
      break;
    case PointMatchState:
    case SelectState:
    default:
      FATAL_ENGAUGE("bad value for state");
  }

  // update all views so point appears
  ASSERT_ENGAUGE(p != 0);
  slotUpdateViews(0, p->boundingRect());

  // update all views so lines appear
  updateFromList(&updateRectList);

  return p;
}

void DigitDoc::addAxisPoint(int xScreen, int yScreen, double xGraph, double yGraph)
{
  m_modified = true;

  // new canvas item object
  Point* p = new Point(xScreen, yScreen, xGraph, yGraph, &m_canvas);
  CHECK_PTR_ENGAUGE(p);

  Q3ValueList<QRect> updateRectList;
  m_dirtyAxesTransformation = true;
  m_pointSets->addPointAxes(&m_canvas, p, &updateRectList);

  // update all views so point appears
  ASSERT_ENGAUGE(p != 0);
  slotUpdateViews(0, p->boundingRect());

  // update all views so lines appear
  updateFromList(&updateRectList);
}
    
void DigitDoc::setAxisPoint(Point* p, double xThetaGraph, double yRGraph)
{
  m_dirtyAxesTransformation = true;

  ASSERT_ENGAUGE(p != 0);
  p->setXThetaGraph(xThetaGraph);
  p->setYRGraph(yRGraph);

  bool validBefore = validAxes();
  computeTransformation();
  if (validBefore != validAxes())
    emit(transformationChange());
}

void DigitDoc::setScalePoint(Point* p, double x, double y)
{
  m_dirtyScaleTransformation = true;

  ASSERT_ENGAUGE(p != 0);
  p->setXThetaGraph(x);
  p->setYRGraph(y);

  bool validBefore = validScale();
  computeTransformation();
  if (validBefore != validScale())
    emit(transformationChange());
}

void DigitDoc::removeGestatingPoint(Point* p)
{
  Q3ValueList<QRect> updateRectList;

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->removePoint(p, &updateRectList);

  // update all views
  updateFromList(&updateRectList);
}

void DigitDoc::updateFromList(Q3ValueList<QRect>* updateRectList)
{
  Q3ValueList<QRect>::iterator itr;
  ASSERT_ENGAUGE(updateRectList != 0);
  for (itr = updateRectList->begin(); itr != updateRectList->end(); ++itr)
  {
    QString str;
    str.sprintf("(%d,%d) (%d,%d)", (*itr).left(), (*itr).top(), (*itr).right(), (*itr).bottom());
    DigitDebug::refresh(str);

    slotUpdateViews(0, (*itr));
  }
}

int DigitDoc::axisPointCount(void)
{
  ASSERT_ENGAUGE(m_transform != 0);
  return m_transform->axisPointCount();
}

int DigitDoc::scalePointCount(void)
{
  ASSERT_ENGAUGE(m_transform != 0);
  return m_transform->scalePointCount();
}

void DigitDoc::computeTransformation()
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  const PointSet* pointset = m_pointSets->axes();

  // try for axes transformation first
  ASSERT_ENGAUGE(m_transform != 0);
  if (m_dirtyAxesTransformation)
  {
    m_dirtyAxesTransformation = false;
    m_transform->computeAxesTransformation(m_coordSettings, pointset);
  }

  bool success = m_transform->validAxes();
  if (!success)
  {
    // axes transformation failed so try scale bar transformation
    pointset = m_pointSets->scale();

    if (m_dirtyScaleTransformation)
    {
      m_dirtyScaleTransformation = false;
      m_transform->computeScaleTransformation(m_coordSettings, pointset);
    }
    success = m_transform->validScale();
  }

  if (success)
  {
    if (!m_gridRemovalSettings.gridMesh.initialized)
      initGridRemovalMesh();

    if (!m_gridDisplaySettings.initialized)
      initGridDisplayMesh();
  }

  // graph coordinates are updated even if transform is invalid, since graph coordinates
  // are just set to screen coordinates
  Q3ValueList<QRect> updateRectList;
  m_pointSets->updateGraphCoordinates(m_coordSettings, m_transform, &updateRectList);

  // update all views so lines appear
  updateFromList(&updateRectList);

  if (success)
    makeGridDisplayLines();
}

bool DigitDoc::gridDisplay()
{
  if (m_gridDisplay)
    return m_gridDisplay->grid();

  return false;
}

void DigitDoc::showGridDisplay(bool toggle)
{
  if (m_gridDisplay)
    m_gridDisplay->showGrid(toggle);

  slotUpdateViews(0, m_canvas.rect());
}

void DigitDoc::setGridRemovalSettings(GridRemovalSettings settings)
{
  m_modified = true;

  m_gridRemovalSettings = settings;

  processOriginalPixmap();
}

void DigitDoc::setGridDisplaySettings(GridMeshSettings settings, bool show)
{
  m_modified = true;

  m_gridDisplaySettings = settings;
  makeGridDisplayLines();

  showGridDisplay(show);
}

void DigitDoc::makeGridDisplayLines()
{
  ASSERT_ENGAUGE(m_gridDisplay != 0);
  bool show = m_gridDisplay->grid();

  m_gridDisplay->makeGridLines(m_transform, m_coordSettings, m_gridDisplaySettings);

  if (show)
    showGridDisplay(show);
}

void DigitDoc::setSegmentSettings(SegmentSettings settings)
{
  m_modified = true;

  // this method is called when user has updated the segment settings, which
  // is an indication that segments are indeed wanted, so unset cmdLazySegments
  cmdLazySegments = false;
  
  m_segmentSettings = settings;
  ASSERT_ENGAUGE(m_segments != 0);
  m_segments->setSettings(settings);

  processOriginalPixmap();

  // state transitions involving segment state require hiding or showing segments
  if (m_digitizeState == SegmentState)
    showSegments(true);
}

void DigitDoc::setPointMatchSettings(PointMatchSettings settings)
{
  m_pointMatchSettings = settings;
}

void DigitDoc::setDiscretizeSettings(DiscretizeSettings settings)
{
  m_discretizeSettings = settings;

  processOriginalPixmap();
}

bool DigitDoc::validAxes(void)
{
  ASSERT_ENGAUGE(m_transform != 0);
  return m_transform->validAxes();
}

bool DigitDoc::validScale(void)
{
  ASSERT_ENGAUGE(m_transform != 0);
  return m_transform->validScale();
}

bool DigitDoc::validAxisPoint(double xTheta, double yR)
{
  if ((m_coordSettings.xThetaScale == Log) &&
    (xTheta <= 0.0))
    return false;
  if ((m_coordSettings.yRScale == Log) &&
    (yR <= 0.0))
    return false;

  return true;
}

void DigitDoc::initGridRemovalMesh()
{
  initGridMesh(&m_gridRemovalSettings.gridMesh);
}

void DigitDoc::initGridDisplayMesh()
{
  initGridMesh(&m_gridDisplaySettings);
}

void DigitDoc::initGridMesh(GridMeshSettings* gridSettings)
{
  gridSettings->initialized = false;

  ASSERT_ENGAUGE(m_transform != 0);
  if (!m_transform->validAxes())
    return;
    
  m_modified = true;
  
  gridSettings->gridSetX = AllButStep;
  gridSettings->gridSetY = AllButStep;

  double xThetaMin, xThetaMax, yRMin, yRMax;

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->pointSetGraphLimits(m_coordSettings, m_transform,
    &xThetaMin, &xThetaMax, &yRMin, &yRMax);

  axisScale(xThetaMin, xThetaMax, (m_coordSettings.xThetaScale == Linear),
    &gridSettings->startX,
    &gridSettings->stopX,
    &gridSettings->stepX,
    &gridSettings->countX);
  axisScale(yRMin, yRMax, (m_coordSettings.yRScale == Linear),
    &gridSettings->startY,
    &gridSettings->stopY,
    &gridSettings->stepY,
    &gridSettings->countY);

  gridSettings->initialized = true;
}

void DigitDoc::setCoordSettings(CoordSettings settings)
{
  // sanity check of axis points
  double xThetaMin, xThetaMax, yRMin, yRMax;
  ASSERT_ENGAUGE(m_pointSets != 0);
  if (m_pointSets->axisSetGraphLimits(settings, m_transform,
    &xThetaMin, &xThetaMax, &yRMin, &yRMax))
  {
    bool badGraph =
      ((settings.xThetaScale == Log) && (xThetaMin <= 0.0)) ||
      ((settings.yRScale == Log) && (yRMin <= 0.0));

    if (badGraph)
    {
      QMessageBox::critical(0, tr("Range error for log scale!"),
        tr("Cannot select log scale when any axis points have zero or\n"
        "negative coordinates. The new settings will be ignored"));
      return;
    }
  }

  m_dirtyAxesTransformation = true;
  m_dirtyScaleTransformation = true;
  
  // sanity checks of grid lines
  bool badGridRemoval = m_gridRemovalSettings.gridMesh.initialized && (
    ((settings.xThetaScale == Log) && (m_gridRemovalSettings.gridMesh.startX <= 0.0)) ||
    ((settings.yRScale == Log) && (m_gridRemovalSettings.gridMesh.startY <= 0.0)));
  bool badGridDisplay = m_gridDisplaySettings.initialized && (
    ((settings.xThetaScale == Log) && (m_gridDisplaySettings.startX <= 0.0)) ||
    ((settings.yRScale == Log) && (m_gridDisplaySettings.startY <= 0.0)));

  m_modified = true;
  m_coordSettings = settings;

  // if necessary, quietly fix the grid lines to be consistent with log scale.
  // originally a warning message (with cancel option) was displayed, but this
  // confused people who did not even know there were grid lines, let alone
  // that the grid, that was automatically generated for linear mode, needed
  // to be fixed
  if (badGridRemoval)
    m_gridRemovalSettings.gridMesh.initialized = false;
  if (badGridDisplay)
    m_gridDisplaySettings.initialized = false;
  if (badGridRemoval || badGridDisplay)
    computeTransformation();
}

PointSetStyle DigitDoc::axesStyle(void)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  return m_pointSets->axesStyle();
}

PointSetStyle DigitDoc::curveStyle(QString name)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  return m_pointSets->curveStyle(name);
}

PointSetStyle DigitDoc::scaleStyle(void)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  return m_pointSets->scaleStyle();
}

void DigitDoc::setAxesStyle(PointSetStyle pointSetStyle)
{
  m_modified = true;

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->setAxesStyle(pointSetStyle);

  // update all views so all points reflect the new style
  slotUpdateViews(0, m_canvas.rect());
}

void DigitDoc::setMatchSetStyle(PointSetStyle pointSetStyle)
{
  if (m_matchSet != 0)
  {
    m_matchSet->setPointSetStyle(pointSetStyle);

    // update all views so all points reflect the new style
    slotUpdateViews(0, m_canvas.rect());
  }
}
    
void DigitDoc::setScaleStyle(PointSetStyle pointSetStyle)
{
  m_modified = true;

  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->setScaleStyle(pointSetStyle);

  // update all views so all points reflect the new style
  slotUpdateViews(0, m_canvas.rect());
}

void DigitDoc::print()
{
  QPrinter printer;
  QPainter p;

  // TODO the pagesize default should be editable in an options dialog
  printer.setPageSize(QPrinter::Letter);

  if (printer.setup())
  {
    p.begin(&printer);
    m_canvas.drawArea(m_canvas.rect(), &p);
    p.end();
  }
}

QString DigitDoc::filterImport()
{
  QString filter(tr("Images (*.bmp *.gif *.jpg *.png *.pnm *.pbm *.xpm);;All Files (*.*)"));

  if (cmdOnlyBmp)
    filter = tr("Images (*.bmp);;All Files (*.*)");

  return filter;
}

QString DigitDoc::filterOpenSave()
{
  return QString("Engauge Digitizer (*%1);;All Files (*.*)")
    .arg(extensionDig);
}

void DigitDoc::dump()
{
  qDebug("document %s", m_title.latin1());
  qDebug("document modified %s", (m_modified ? "yes" : "no"));
  qDebug("document state %d", m_digitizeState);
  qDebug("document coord frame %d xthetascale %d yrscale %d thetaunits %d",
    m_coordSettings.frame,
    m_coordSettings.xThetaScale,
    m_coordSettings.yRScale,
    m_coordSettings.thetaUnits);
  qDebug("document export points selection %d layout %d delimiters %d header %d",
    m_exportSettings.pointsSelection,
    m_exportSettings.layout,
    m_exportSettings.delimiters,
    m_exportSettings.header);
  qDebug("document grid removal thinLines '%s' thinThickness %f gridlines '%s' gridDistance %f color '%s' color r=%d/g=%d/b=%d",
    (m_gridRemovalSettings.removeThinLines ? "yes" : "no"),
    m_gridRemovalSettings.thinThickness,
    (m_gridRemovalSettings.removeGridlines ? "yes" : "no"),
    m_gridRemovalSettings.gridDistance,
    (m_gridRemovalSettings.removeColor ? "yes" : "no"),
    m_gridRemovalSettings.color.red(),
    m_gridRemovalSettings.color.green(),
    m_gridRemovalSettings.color.blue());
  if (m_gridRemovalSettings.gridMesh.initialized)
    qDebug("document grid removal counts %d/%d steps %f/%f starts %f/%f stops %f/%f",
      m_gridRemovalSettings.gridMesh.countX,
      m_gridRemovalSettings.gridMesh.countY,
      m_gridRemovalSettings.gridMesh.stepX,
      m_gridRemovalSettings.gridMesh.stepY,
      m_gridRemovalSettings.gridMesh.startX,
      m_gridRemovalSettings.gridMesh.startY,
      m_gridRemovalSettings.gridMesh.stopX,
      m_gridRemovalSettings.gridMesh.stopY);
  else
    qDebug("document grid removal mesh 'uninitialized'");
  if (m_gridDisplaySettings.initialized)
    qDebug("document grid display counts %d/%d steps %f/%f starts %f/%f stops %f/%f",
      m_gridDisplaySettings.countX,
      m_gridDisplaySettings.countY,
      m_gridDisplaySettings.stepX,
      m_gridDisplaySettings.stepY,
      m_gridDisplaySettings.startX,
      m_gridDisplaySettings.startY,
      m_gridDisplaySettings.stopX,
      m_gridDisplaySettings.stopY);
  else
    qDebug("document grid display mesh 'uninitialized'");
  qDebug("document segment settings minpoints %d pointseparation %d linesize %d linecolor %d",
    m_segmentSettings.minPoints,
    m_segmentSettings.pointSeparation,
    m_segmentSettings.lineSize,
    m_segmentSettings.lineColor);
  qDebug("document point match settings pointseparation %d pointsize %d",
    m_pointMatchSettings.pointSeparation,
    m_pointMatchSettings.pointSize);
  qDebug("document discretize settings method %d intensity %d/%d foreground %d/%d hue %d/%d saturation %d/%d value %d/%d",
    m_discretizeSettings.discretizeMethod,
    m_discretizeSettings.intensityThresholdLow,
    m_discretizeSettings.intensityThresholdHigh,
    m_discretizeSettings.foregroundThresholdLow,
    m_discretizeSettings.foregroundThresholdHigh,
    m_discretizeSettings.hueThresholdLow,
    m_discretizeSettings.hueThresholdHigh,
    m_discretizeSettings.saturationThresholdLow,
    m_discretizeSettings.saturationThresholdHigh,
    m_discretizeSettings.valueThresholdLow,
    m_discretizeSettings.valueThresholdHigh);
  
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->dump();
  ASSERT_ENGAUGE(m_segments != 0);
  m_segments->dump();
  ASSERT_ENGAUGE(m_transform != 0);
  m_transform->dump();
  // since match points list is typically extremely long, which causes
  // previous information to scroll offscreen, we omit match points here
}

void DigitDoc::finishMove()
{
  m_modified = true;

  // recompute transformation and apply to all points. this is wasteful if
  // only a few pointset points were moved (transformation and most points would be
  // changed unnecessarily) but the extra time spent is short and this code is simple
  m_dirtyAxesTransformation = true;
  m_dirtyScaleTransformation = true;
  computeTransformation();

  sendUpdateGeometry();
}

QString DigitDoc::curveCmbText()
{
  ASSERT_ENGAUGE(!m_curveCmbText.isEmpty());

  return m_curveCmbText;
}

QString DigitDoc::measureCmbText()
{
  ASSERT_ENGAUGE(!m_measureCmbText.isEmpty());

  return m_measureCmbText;
}

void DigitDoc::setCurveCmbText(QString curveCmbText)
{
  QStringList list;
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->curveNames(&list);

  if (list.find(curveCmbText) == list.end())
    FATAL_ENGAUGE(QObject::tr("could not find %1 among curve names: %2")
      .arg(curveCmbText.latin1())
      .arg(list.join(QString(" ")).latin1()));

  m_curveCmbText = curveCmbText;
}

void DigitDoc::setMeasureCmbText(QString measureCmbText)
{
  QStringList list;
  ASSERT_ENGAUGE(m_pointSets != 0);
  m_pointSets->measureNames(&list);

  if (list.find(measureCmbText) == list.end())
    FATAL_ENGAUGE(QObject::tr("could not find %1 among measure names: %2")
      .arg(measureCmbText.latin1())
      .arg(list.join(QString(" ")).latin1()));

  m_measureCmbText = measureCmbText;
}

void DigitDoc::selectionListChanged()
{
  emit(selectionChange());
}

void DigitDoc::showSegments(bool show)
{
  // make segments visible
  Q3ValueList<QRect> updateRectList;
  ASSERT_ENGAUGE(m_segments != 0);
  m_segments->showSegments(show, m_segmentSettings, &updateRectList);

  // do not update using updateRectList since that suffers from bad flicker
  slotUpdateViews(0, m_canvas.rect());
}

void DigitDoc::setViewPointSelection(ViewPointSelection viewPointSelection)
{
  m_viewPointSelection = viewPointSelection;

  ASSERT_ENGAUGE(m_pointSets != 0);
  switch (viewPointSelection)
  {
    case ViewAxesPoints:
      m_pointSets->showAxesPoints();
      break;
    case ViewScalePoints:
      m_pointSets->showScalePoints();
      break;
    case ViewCurvePoints:
      m_pointSets->showCurvePoints(m_curveCmbText);
      break;
    case ViewMeasurePoints:
      m_pointSets->showMeasurePoints(m_measureCmbText);
      break;
    case ViewAllPoints:
      m_pointSets->showAllPoints();
      break;
  }

  slotUpdateViews(0, m_canvas.rect());
}

ViewPointSelection DigitDoc::viewPointSelection()
{
  return m_viewPointSelection;
}

void DigitDoc::setBackground(BackgroundSelection selection)
{
  m_backgroundSelection = selection;
  m_canvas.setBackground(selection);
}

BackgroundSelection DigitDoc::background()
{
  return m_backgroundSelection;
}

void DigitDoc::highlightCandidateMatchPoint(const QPoint &p)
{
  ASSERT_ENGAUGE(m_digitizeState == PointMatchState);

  Discretize discretize;
  if (discretize.processedPixelIsOn(m_processedImage, p.x(), p.y()))
  {
    // pixel is on
    bool found = (m_samplePointPixels.size() > 0);
    if (found)
      found = m_samplePointPixels.containsPoint(QPoint(p.x(), p.y()), Qt::OddEvenFill);

    if (!found)
    {
      // if max point size is set to huge value, the n-squared search algorithm will bog down
      // so show user the wait cursor. bog was seen for a pixel count of about 8000
      QApplication::setOverrideCursor(Qt::WaitCursor);
  
      // process new point
      m_samplePointPixels.resize(0);
      PointMatch pointMatch;
      pointMatch.isolateSampleMatchPoint(&m_samplePointPixels,
        m_processedImage, m_pointMatchSettings,
        p.x(), p.y(), p.x(), p.y());
      addSampleMatchPointToViews();

      QApplication::restoreOverrideCursor();
    }

    return;
  }

  // pixel is off
  m_samplePointPixels.resize(0);
  removeSampleMatchPointFromViews();
}

void DigitDoc::addSampleMatchPointToViews()
{
  DigitView* view;
  for(view = m_viewList->first(); view != 0; view = m_viewList->next())
    view->addSampleMatchPoint(m_samplePointPixels);
}

void DigitDoc::removeSampleMatchPointFromViews()
{
  DigitView* view;
  for(view = m_viewList->first(); view != 0; view = m_viewList->next())
    view->removeSampleMatchPoint();
}

bool DigitDoc::matchSamplePoint(QPoint p)
{
  // fail if there is no sample point under the cursor
  if (!m_samplePointPixels.containsPoint(QPoint(p.x(), p.y()), Qt::OddEvenFill))
    return false;

  // start with existing points in current pointset
  Q3PointArray pointsExisting = m_pointSets->curveCoordinates(m_curveCmbText);

  // matching step is slow (on the order of several seconds) so show hourglass
  QApplication::setOverrideCursor(Qt::WaitCursor);

  // assemble list of matching points
  Q3ValueList<PointMatchTriplet> pointsCreated;
  PointMatch::matchSamplePoint(m_processedImage, m_pointMatchSettings,
    m_samplePointPixels, pointsExisting, &pointsCreated);

  // computations are over
  QApplication::restoreOverrideCursor();

  if (pointsCreated.count() < 1)
  {
    QMessageBox::critical(0, tr("Point Match Error!"), tr("No points successfully matched the sample point!\n"
      "Skipping the matching of sample points using arrow keys"), QMessageBox::Ok, Qt::NoButton);
  }
  else
  {
    Q3ValueList<QRect> updateRectList;
    ASSERT_ENGAUGE(m_matchSet != 0);
    m_matchSet->addCreatedPointsToCanvas(&m_canvas,
      curveStyle(m_curveCmbText),
      m_pointMatchSettings,
      &pointsCreated,
      &updateRectList);

    // update all views
    updateFromList(&updateRectList);

    forwardNormalMsg(QString(tr("Right=Accept, Space=Reject, Left=Remove. Select to exit")));
  }
  
  return true;
}

void DigitDoc::matchPointAccept()
{
  Q3ValueList<QRect> updateRectList;

  ASSERT_ENGAUGE(m_matchSet != 0);
  if (m_matchSet->matchPointAccept(&updateRectList))
  {
    // update all views
    updateFromList(&updateRectList);
  }
}

void DigitDoc::matchPointReject()
{
  Q3ValueList<QRect> updateRectList;

  ASSERT_ENGAUGE(m_matchSet != 0);
  if (m_matchSet->matchPointReject(&updateRectList))
  {
    // update all views
    updateFromList(&updateRectList);
  }
}

void DigitDoc::matchPointRemove()
{
  Q3ValueList<QRect> updateRectList;

  ASSERT_ENGAUGE(m_matchSet != 0);
  if (m_matchSet->matchPointRemove(&updateRectList))
  {
    // update all views
    updateFromList(&updateRectList);
  }
}

void DigitDoc::cleanUpAcceptedPoints(DigitizeState state)
{
  Q3ValueList<QPoint> acceptedPoints;
  collectAcceptedPoints(&acceptedPoints);

  if (acceptedPoints.count() > 0)
  {
    // accepted points can only be saved as curve or measure points. show a dialog box
    // asking how points should be saved, with the default set according to the new state
    QString msg;
    msg = QString("There are %1 accepted points.\n\nHow should they be saved?")
      .arg(acceptedPoints.count());
    int buttonDefault = 2;
    if (state == CurveState)
      buttonDefault = 0;
    else if (state == MeasureState)
      buttonDefault = 1;

    int buttonChose = QMessageBox::information(0, title(), msg,
      QString(tr("Curve")), QString(tr("Measure")), QString(tr("Do not save")), buttonDefault, 2);
    if (buttonChose == 0)
    {
      m_digitizeState = CurveState;
      addAcceptedPoints(&acceptedPoints);
    }
    else if (buttonChose == 1)
    {
      m_digitizeState = MeasureState;
      addAcceptedPoints(&acceptedPoints);
    }
  }
  
  clearAcceptedPoints();
}

void DigitDoc::collectAcceptedPoints(Q3ValueList<QPoint>* acceptedPoints)
{
  // get accepted points in point match
  ASSERT_ENGAUGE(m_matchSet != 0);
  m_matchSet->acceptedPoints(acceptedPoints);
}

void DigitDoc::addAcceptedPoints(Q3ValueList<QPoint>* acceptedPoints)
{
  Q3ValueList<QPoint>::iterator itr;
  ASSERT_ENGAUGE(acceptedPoints != 0);
  for (itr = acceptedPoints->begin(); itr != acceptedPoints->end(); ++itr)
    addPoint((*itr).x(), (*itr).y());
}

void DigitDoc::clearAcceptedPoints()
{
  Q3ValueList<QRect> updateRectList;
  m_matchSet->clear(&updateRectList);

  sendUpdateGeometry();

  // update all views. the previous call to sendUpdateGeometry cleaned
  // up the points, but it left behind the highlights 
  updateFromList(&updateRectList);
}

bool DigitDoc::geometryInfoCurve(GeometryWindowItemList& rInfo)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  bool mod = m_pointSets->modifiedGeometryCurve(m_curveCmbText);
  if (mod)
  {
    computeTransformation();

    ASSERT_ENGAUGE(m_transform != 0);
    m_pointSets->geometryInfoCurve(
      m_transform->validAxes() || m_transform->validScale(),
      m_coordSettings.frame == Cartesian,
      m_curveCmbText,
      rInfo);
  }

  return mod;
}

bool DigitDoc::geometryInfoMeasure(GeometryWindowItemList& rInfo)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  bool mod = m_pointSets->modifiedGeometryMeasure(m_measureCmbText);
  if (mod)
  {
    computeTransformation();

    ASSERT_ENGAUGE(m_transform != 0);
    m_pointSets->geometryInfoMeasure(
      m_transform->validAxes() || m_transform->validScale(),
      m_coordSettings.frame == Cartesian,
      m_measureCmbText,
      rInfo);
  }

  return mod;
}

void DigitDoc::sendUpdateGeometry()
{
  emit(updateGeometry());
}

bool DigitDoc::findView(DigitView* viewLookup)
{
  DigitView* view;
  for(view = m_viewList->first(); view != 0; view = m_viewList->next())
  {
    if (view == viewLookup)
      return true;
  }

  return false;
}

void DigitDoc::DigitCanvas::setBackground(BackgroundSelection selection)
{
  switch (selection)
  {
  case BlankBackground:
    {
      QPixmap empty(m_doc->originalPixmap().width(), m_doc->originalPixmap().height());
      empty.fill(Qt::white);
      Q3Canvas::setBackgroundPixmap(empty);
    }
    break;
  case OriginalImage:
    Q3Canvas::setBackgroundPixmap(m_doc->originalPixmap());
    break;
  case ProcessedImage:
    Q3Canvas::setBackgroundPixmap(m_doc->processedPixmap());
    break;
  }

  updateBackground();
}

void DigitDoc::DigitCanvas::updateBackground()
{
  // according to QCanvas::drawBackground documentation this is needed to force the redraw
  setChanged(QRect(0, 0, m_doc->originalImage().width(), m_doc->originalImage().height()));
}

QPixmap DigitDoc::curveThumbnail(QString name)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  return m_pointSets->curveThumbnail(name);
}

QPixmap DigitDoc::measureThumbnail(QString name)
{
  ASSERT_ENGAUGE(m_pointSets != 0);
  return m_pointSets->measureThumbnail(name);
}

void DigitDoc::scanForAxes(double xMinG, double xMaxG, double yMinG, double yMaxG)
{
  ScanForAxes scanner(xMinG, xMaxG, yMinG, yMaxG, this);
  scanner.execute();
}

void DigitDoc::startShowOnlySelectedCurve()
{
  if (!m_inViewPointSelectionOverride)
  {
    m_inViewPointSelectionOverride = true;

    // store initial selection before overriding
    m_viewPointSelectionSaved = m_viewPointSelection;
    
    // override selection
    setViewPointSelection(ViewCurvePoints);
  }
}

void DigitDoc::stopShowOnlySelectedCurve()
{
  if (m_inViewPointSelectionOverride)
  {
    m_inViewPointSelectionOverride = false;

    // restore initial selection before override
    setViewPointSelection(m_viewPointSelectionSaved);
  }
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void DigitDoc::slotUpdateViews(DigitView* sender, QRect boundingRect)
{
  // TODO - consider changing this from a slot to a regular member function
  DigitView* view;
  for(view = m_viewList->first(); view != 0; view = m_viewList->next())
    view->update(sender, boundingRect);
}
