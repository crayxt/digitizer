/***************************************************************************
                          defaultsettings.h  -  description
                             -------------------
    begin                : Thu Sep 9 2004
    copyright            : (C) 2004 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: defaultsettings.h,v $
    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.10  2004/10/29 03:06:13  markmitch
    Scan for axes works up to generating axis points

    Revision 1.9  2004/10/12 03:51:26  markmitch
    Save view selections

    Revision 1.8  2004/10/08 07:41:37  markmitch
    Glossary. Sessions settings

    Revision 1.7  2004/10/07 07:55:47  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.6  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.4  2004/09/26 08:42:10  markmitch
    Most recently used document list

    Revision 1.3  2004/09/22 06:42:00  markmitch
    Settings can be saved in text file in Windows

    Revision 1.2  2004/09/13 08:32:31  markmitch
    Table-based geometry windows

    Revision 1.1  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.2  2004/09/12 04:52:14  markmitch
    Most settings are saved. Command line usage in Windows

    Revision 1.1  2004/09/11 05:59:18  markmitch
    First phase of settings archival


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef DEFAULTSETTINGS_H
#define DEFAULTSETTINGS_H

#include <qcolor.h>
#include <qpoint.h>
#include <qsize.h>
#include <qsettings.h>

#include "digitdef.h"

// this singleton class saves and restores default program settings, which
// are a mixture of the original default settings (read in during startup) and
// the settings of all of the documents that have been opened so far. these
// default settings are saved during program shutdown for use in other sessions
class DefaultSettings
{
  public:

    static void create(void)
    {
      if (!m_settings)
        m_settings = new DefaultSettings;
    }
    static void destroy(void)
    {
      if (m_settings)
      {
        delete m_settings;
        m_settings = 0;
      }
    }
    static DefaultSettings& instance(void)
    {
      return *m_settings;
    }

    // get methods. where possible, these return structures to reduce the number of methods
    CoordSettings getCoordSettings();
    ExportSettings getExportSettings();
    bool getViewFileToolbar();
    bool getViewSelectToolbar();
    bool getViewImageScaleToolbar();
    bool getViewDigitizeCurvePointsToolbar();
    bool getViewDigitizeMeasurePointsToolbar();
    bool getViewZoomToolbar();
    bool getViewStatusBar();
    ViewPointSelection getViewPoints();
    BackgroundSelection getViewBackground();
    bool getViewCurveGeometry();
    bool getViewMeasureGeometry();
    int getPowerMostSigMax();
    int getPowerMostSigMin();
    double getDoubleMin();
    int getMaxCommands();
    QPoint getWindowCurvePosition();
    QSize getWindowCurveSize();
    QPoint getWindowHelpPosition();
    QSize getWindowHelpSize();
    QPoint getWindowMainPosition();
    QSize getWindowMainSize();
    QPoint getWindowMeasurePosition();
    QSize getWindowMeasureSize();
    bool getWindowMainFontOverride();
    QString getWindowMainFontName();
    int getWindowMainFontSize();
    int getKeyClipboard();
    int getKeyTree();
    int getKeyVariables();
    QSize getHandleSize();
    SegmentSettings getSegmentSettings();
    int getSegmentPointMinSeparation();
    GridRemovalSettings getGridRemovalSettings();
    GridSet getGridDisplayGridSetX();
    GridSet getGridDisplayGridSetY();
    int getPointMatchHighlightDiameter();
    int getPointMatchHighlightLineSize();
    PointMatchSettings getPointMatchSettings();
    DiscretizeSettings getDiscretizeSettings();
    PointSetStyle getAxesStyle();
    PointSetStyle getScaleStyle();
    PointSetStyle getCurveStyle(int pointSetIndex);
    PointSetStyle getMeasureStyle(int pointSetIndex);
    int getMruMax();
    QStringList getMruDocuments();
    int getComboBoxWidthMin();
    SessionsSettings getSessionsSettings();
    Color getScanForAxesLineColor();
    int getScanForAxesLineWidth();
    int getScanForAxesEndpointKernelWidth();
    bool getScanForAxesScanEffect();

    // set methods. for simplicity, these accept structures used by external code
    void setCoordSettings(CoordSettings coord);
    void setDiscretizeSettings(DiscretizeSettings discretize);
    void setExportSettings(ExportSettings exportSettings);
    void setViewBackground(BackgroundSelection view);
    void setViewCurveGeometry(bool view);
    void setViewDigitizeCurvePointsToolbar(bool view);
    void setViewDigitizeMeasurePointsToolbar(bool view);
    void setViewFileToolbar(bool view);
    void setViewImageScaleToolbar(bool view);
    void setViewMeasureGeometry(bool view);
    void setViewPoints(ViewPointSelection view);
    void setViewSelectToolbar(bool view);
    void setViewStatusBar(bool view);
    void setViewZoomToolbar(bool view);
    void setGridRemovalSettings(GridRemovalSettings grid);
    void setGridDisplaySettings(GridMeshSettings grid);
    void setPointMatchSettings(PointMatchSettings match);
    void setSegmentSettings(SegmentSettings seg);
    void setWindowCurvePosition(QPoint pos);
    void setWindowCurveSize(QSize size);
    void setWindowHelpPosition(QPoint pos);
    void setWindowHelpSize(QSize size);
    void setWindowMainPosition(QPoint pos);
    void setWindowMainSize(QSize size);
    void setWindowMeasurePosition(QPoint pos);
    void setWindowMeasureSize(QSize size);
    void setAxesStyle(PointSetStyle style);
    void setScaleStyle(PointSetStyle style);
    void setCurveStyles(const PointSetStyleList& rStyles);
    void setMeasureStyles(const PointSetStyleList& rStyles);
    void setMruMax(int mruMax);
    void setMruDocuments(const QStringList& rMruDocuments);
    void setComboBoxWidthMin(int comboBoxWidthMin);
    void setSessionsSettings(SessionsSettings sessionsSettings);
    
    // save current settings just before exiting the application
    void archiveSettings();

  protected:

    DefaultSettings();
    ~DefaultSettings();

  private:

    // user controls a set of flags that determine what gets saved
    SessionsSettings m_sessionsSettings;

    // settings are initialized to factory defaults, then the archived values are merged in
    void initializeSettingsToFactoryDefaults();
    void loadArchivedSettings();
    void loadMruDocuments(QSettings& rArchiver);
    void loadPointSetStyle(PointSetStyle& rStyle,
      QSettings& rArchiver,
      const QString keyPointShape,
      const QString keyPointSize,
      const QString keyPointLineSize,
      const QString keyPointLineColor,
      const QString keyPointInColor,
      const QString keyLineSize,
      const QString keyLineColor,
      const QString keyLineConnectAs);
    void loadPointSetStyles(bool isCurve,
      PointSetStyleList& rStyleList,
      QSettings& rArchiver,
      const QString keyGroupPrefix,
      const QString keyPointShape,
      const QString keyPointSize,
      const QString keyPointLineSize,
      const QString keyPointLineColor,
      const QString keyPointInColor,
      const QString keyLineSize,
      const QString keyLineColor,
      const QString keyLineConnectAs);

    // singleton instance
    static DefaultSettings* m_settings;

    // coordinate settings
    CoordSettings m_coordSettings;

    // export settings
    ExportSettings m_exportSettings;

    // view selections
    bool m_viewFileToolbar;
    bool m_viewSelectToolbar;
    bool m_viewImageScaleToolbar;
    bool m_viewDigitizeCurvePointsToolbar;
    bool m_viewDigitizeMeasurePointsToolbar;
    bool m_viewZoomToolbar;
    bool m_viewStatusBar;
    ViewPointSelection m_viewPoints;
    BackgroundSelection m_viewBackground;
    bool m_viewCurveGeometry;
    bool m_viewMeasureGeometry;
  
    // status bar coordinates having powers outside the min-to-max range are displayed
    // in exponential format since there would be too many digits to make identifying
    // the magnitude reasonably easy
    int m_powerMostSigMax;
    int m_powerMostSigMin;

    // any number between -DoubleMin and +DoubleMin is considered to be zero. useful
    // info for this is at http://www.math.byu.edu/~schow/work/IEEEFloatingPoint.htm
    double m_doubleMin;

    // command do/undo. the value must be computed so that available memory is not exceeded
    unsigned int m_maxCommands;

    // choose curve geometry window size so it completely fits on small 800x600 screens
    QPoint m_windowCurvePosition;
    QSize m_windowCurveSize;

    // choose help window size so it completely fits on small 800x600 screens
    QPoint m_windowHelpPosition;
    QSize m_windowHelpSize;
            
    // choose main window size so it completely fits on small 800x600 screens
    QPoint m_windowMainPosition;
    QSize m_windowMainSize;
    bool m_windowMainFontOverride;
    QString m_windowMainFontName;
    int m_windowMainFontSize;
    int m_windowMainComboBoxWidthMin;
    
    // choose measure geometry window size so it completely fits on small 800x600 screens
    QPoint m_windowMeasurePosition;
    QSize m_windowMeasureSize;

    // keystrokes for debug dumps
    int m_keyClipboard; // clipboard contents
    int m_keyTree; // document QObject tree. no output for release version of Qt library
    int m_keyVariables; // document member variables

    // width and height of handles around selected objects, in pixels
    QSize m_handleSize;

    // segment settings
    int m_segmentPointMinSeparation;
    SegmentSettings m_segmentSettings;

    // gridline removal defaults
    GridRemovalSettings m_gridRemovalSettings;

    // grid display defaults
    GridSet m_gridDisplayGridSetX;
    GridSet m_gridDisplayGridSetY;

    // match points separation default and minimum
    int m_pointMatchHighlightDiameter;
    int m_pointMatchHighlightLineSize;
    PointMatchSettings m_pointMatchSettings;

    // discretization defaults
    DiscretizeSettings m_discretizeSettings;

    // pointset styles
    PointSetStyle m_axesStyle;
    PointSetStyle m_scaleStyle;
    PointSetStyleList m_curveStyles;
    PointSetStyleList m_measureStyles;

    // most recently used documents
    int m_mruMax;
    QStringList m_mruDocuments;

    // scan for axes algorith defaults
    Color m_scanForAxesLineColor;
    int m_scanForAxesLineWidth;
    int m_scanForAxesEndpointKernelWidth;
    bool m_scanForAxesScanEffect;
};

#endif // DEFAULTSETTINGS_H
