/***************************************************************************
                          digitdef.h  -  description
                             -------------------
    begin                : Fri Nov 1 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: digitdef.h,v $
    Revision 1.7  2006/12/20 08:20:25  markmitch
    Rework of point matching to handle skipping

    Revision 1.6  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.3  2006/09/24 06:07:14  markmitch
    New date/time converter

    Revision 1.3.2.2  2006/09/13 06:17:02  markmitch
    Polar plot with origin offset works. Invalid axis/scale point combos prevented

    Revision 1.3.2.1  2006/09/08 07:03:36  markmitch
    Nonzero origin radius. Bugs: Not serialized, maybe nonzero+log issue

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.68  2004/10/28 04:54:31  markmitch
    Scan for axes

    Revision 1.67  2004/10/25 23:55:15  markmitch
    Export command line option. Select initial state

    Revision 1.66  2004/10/18 23:00:53  markmitch
    Version numbers are now strings since 2.1 is not 2.10. Fixed displaying wrong points with multiple documents

    Revision 1.65  2004/10/16 04:35:21  markmitch
    Version 2.10

    Revision 1.64  2004/10/15 03:30:36  markmitch
    Fill corners option in segment fill

    Revision 1.63  2004/10/12 03:51:26  markmitch
    Save view selections

    Revision 1.62  2004/10/08 07:41:37  markmitch
    Glossary. Sessions settings

    Revision 1.61  2004/10/05 04:00:48  markmitch
    Combobox color reflects digitize state

    Revision 1.60  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.58  2004/09/26 08:42:10  markmitch
    Most recently used document list

    Revision 1.57  2004/09/18 14:19:03  markmitch
    Upgrade to Qt 3.3.3 fixes problems with linux clipboard pasting

    Revision 1.56  2004/09/15 04:43:27  markmitch
    Drag export geometry. Drag import image

    Revision 1.55  2004/09/13 08:32:31  markmitch
    Table-based geometry windows

    Revision 1.54  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.53  2004/09/12 04:52:14  markmitch
    Most settings are saved. Command line usage in Windows

    Revision 1.52  2004/09/11 05:59:17  markmitch
    First phase of settings archival

    Revision 1.51  2004/09/09 05:33:44  markmitch
    Invoker in work. Windows upgrade to 3.3.3

    Revision 1.50  2004/06/12 17:53:41  markmitch
    MacOSX compatible eyedropper cursor

    Revision 1.49  2004/04/05 05:39:53  markmitch
    Remove Valgrind warning messages

    Revision 1.48  2004/04/01 02:08:23  markmitch
    Version 2.5

    Revision 1.47  2004/03/26 00:55:14  markmitch
    Missing 2.3

    Revision 1.46  2004/02/04 06:26:44  markmitch
    Version 2.4

    Revision 1.45  2004/01/31 18:32:58  markmitch
    Version 2.3

    Revision 1.44  2004/01/25 19:06:58  markmitch
    Version 2.1. Limited recursion. Default grid removal settings

    Revision 1.43  2004/01/14 06:54:37  markmitch
    Point match works well and has documentation

    Revision 1.42  2004/01/13 17:54:06  markmitch
    Testing point match

    Revision 1.41  2004/01/07 07:48:07  markmitch
    Implementing point match

    Revision 1.40  2004/01/06 08:14:39  markmitch
    Point match mode highlights sample point

    Revision 1.39  2004/01/04 08:40:59  markmitch
    Dialog for point match settings

    Revision 1.38  2003/12/30 09:14:32  markmitch
    Color chooser has two formats and can be disabled

    Revision 1.37  2003/12/29 20:51:50  markmitch
    All discretize modes work

    Revision 1.36  2003/12/29 06:55:10  markmitch
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

#ifndef DIGITDEF_H
#define DIGITDEF_H

#include <qstring.h>
#include <qstringlist.h>
#include <q3canvas.h>
#include <q3valuelist.h>

#include "mmsubs.h"

// version information is stored as a number in string format
// so that numerically identical versions (2.1 and 2.10) can be distinguished.
// VersionNumbersSupported is a list of file versions that can be opened by
// this version
extern QString VersionNumber;
extern QStringList VersionNumbersSupported;

// user can specify location of user manual using this environment variable
const QString UserManualEnvironmentVariable("ENGAUGE_USERMANUAL");

// user can specify browser command using this environment variable
const QString BrowserEnvironmentVariable("ENGAUGE_BROWSER");

// global keys that must be kept consistent with menu items in main window
const QString globalKeyCut(QObject::tr("Ctrl+X"));
const QString globalKeyCopy(QObject::tr("Ctrl+C"));
const QString globalKeyPaste(QObject::tr("Ctrl+V"));

// kludge for freeware Qt 2.3.1 so window captions work
extern const char* freewareCaption;

// z values determine which drawn entities overlap others
const double ZGridLines = 0.0; // lower than everything so grid lines are at the bottom
const double ZLines = 1.0; // lower than ZPoints so lines are behind points
const double ZPoints = 2.0; // higher than ZLines so lines are behind points
const double ZSegments = 3.0; // higher than almost everything since segments are only seen in segment mode
const double ZHandles = 4.0; // higher than segments so we can always see selection handles
const double ZScanForAxesLines = 5.0; // higher than segments so we can always see the scan axes lines

// gridline removal limits
const int RemovalMaxRecursion = 4000; // default Windows stack size of 1MB handles recursion depth of 5700

// eyedropper is used to get color of single pixel
const int EyedropperHotX = 0;
const int EyedropperHotY = 15;

// digitize modes
enum DigitizeState
{
  AxisState,
  CurveState,
  MeasureState,
  PointMatchState,
  ScaleState,
  SegmentState,
  SelectState
};

// gridline types
enum GridType
{
  GridTypeRemoval,
  GridTypeDisplay
};

// circles are not allowed as point shapes because the point shapes are drawn
// as polygons so a circle would require too many points (but note that
// QPointArray::makeEllipse would be helpful in this case)
//
// the first curve is assigned the first point shape, and each succeeding curve
// gets the next shape (cycling through the shapes if necessary). we start the
// list with the polygons, and then end with the crosses and x's
enum PointShape
{
  Cross = 0,
  X,
  Diamond,
  Square,
  Triangle,
  MaxPointShape
};

enum PointSize
{
  PointSize1 = 0,
  PointSize2,
  PointSize3,
  PointSize4,
  PointSize5,
  PointSize6,
  PointSize7,
  PointSize8,
  MaxPointSize
};

enum PointLineSize
{
  PointLineSize1 = 0,
  PointLineSize2,
  PointLineSize3,
  PointLineSize4,
  PointLineSize5,
  PointLineSize6,
  PointLineSize7,
  PointLineSize8,
  MaxPointLineSize
};

enum LineSize
{
  LineSize1 = 0,
  LineSize2,
  LineSize3,
  LineSize4,
  LineSize5,
  LineSize6,
  LineSize7,
  LineSize8,
  MaxLineSize
};

// Point line color, point interior color, and line color share the same values
enum Color
{
  DigitBlack = 0,
  DigitBlue,
  DigitCyan,
  DigitGold,
  DigitGreen,
  DigitMagenta,
  DigitRed,
  DigitTransparent,
  DigitYellow,
  DigitMaxColor
};

// Connect As method determines how points are connected by lines
enum LineConnectAs
{
  SingleValuedFunction = 0,
  Contour,
  MaxConnectAsMethod
};

struct PointSetStyle
{
  // cross, diamond, ...
  PointShape pointShape;

  // width and height of point shape. this unitless value is mapped into a pixel value that
  // assumes the point line has a width of one pixel
  PointSize pointSize;

  // width of point line, in pixels
  PointLineSize pointLineSize;

  // color of point shape
  Color pointLineColor;

  // color inside point shape
  Color pointInColor;

  // width of line between points, in pixels
  LineSize lineSize;
  
  // line color
  Color lineColor;

  // connect as method
  LineConnectAs lineConnectAs;
};

typedef Q3ValueList<PointSetStyle> PointSetStyleList;

// reference frame that applies to both x/theta and y/r graph coordinates of a document
enum ReferenceFrame
{
  Cartesian,
  Polar
};

// scale that applies separately to x/theta and y/r coordinates of a document
enum Scale
{
  Linear,
  Log
};

// units that apply to theta polar graph coordinate of a document
enum ThetaUnits
{
  ThetaDegrees,
  ThetaGradians,
  ThetaRadians
};

struct CoordSettings
{
  ReferenceFrame frame;
  double originRadius;
  Scale xThetaScale;
  Scale yRScale;
  ThetaUnits thetaUnits;
};

// methods of determining which points are to be exported
enum ExportPointsSelection
{
  XFromAllCurves, // y from interpolating all curve
  XFromFirstCurve, // y from interpolating all curves
  XFromGridLines, // y from interpolating all curves
  XYFromAllCurves // no interpolation is performed
};

// multicurve layout in exported files
enum ExportLayout
{
  AllCurvesOnEachLine,
  OneCurveOnEachLine
};

// value separators in exported files
enum ExportDelimiters
{
  Commas,
  Spaces,
  Tabs
};

enum ExportHeader
{
  HeaderNone,
  HeaderSimple,
  HeaderGnuplot
};

struct ExportSettings
{
  ExportPointsSelection pointsSelection;
  ExportLayout layout;
  ExportDelimiters delimiters;
  ExportHeader header;
};

// of the four grid mesh parameters (count, increment, start, stop), only 
// three are independent
enum GridSet
{
  AllButCount,
  AllButStart,
  AllButStep,
  AllButStop
};

extern QStringList GridSetStrings;

// display and removal gridline meshes are regularly spaced
struct GridMeshSettings
{
  bool initialized;
  GridSet gridSetX;
  GridSet gridSetY;
  int countX;
  int countY;
  double stepX;
  double stepY;
  double startX;
  double startY;
  double stopX;
  double stopY;
};

// gridline removal is performed by any combination of three approaches
struct GridRemovalSettings
{
  // thinline removal approach
  bool removeThinLines;
  double thinThickness;

  // regular gridline removal approach
  bool removeGridlines;
  GridMeshSettings gridMesh;
  double gridDistance;

  // color gridline removal approach
  bool removeColor;
  QColor color;
  int foregroundThresholdLow;
  int foregroundThresholdHigh;

  // after gridlines are removed, gaps smaller than this value are connected
  double gapSeparation;
};

struct SegmentSettings
{
  // minimum length of segment in points. segments with fewer points are not displayed.
  // smaller value usually causes many more segments to be drawn, which can lengthen
  // drawing time and collision finding (hidden canvas items are never considered during
  // collision finding). memory usage is not affected since segments of all sizes are
  // initially created, so we never have to go back and rescan when minPoints and
  // pointSeparation are modified
  int minPoints;

  // when a segment is digitized, the curve points will be separated by this value in pixels
  // although if fillCorners is on then sometimes the separations will be less
  int pointSeparation;

  // true to have a point at every corner. this option is useful for piecewise-linear graphs
  // because all important information is captured, but smoothly varying graphs can
  // become too cluttered with no benefit gained
  bool fillCorners;

  // width of line between points, in pixels
  LineSize lineSize;

  // line color
  Color lineColor;
};

struct PointMatchSettings
{
  // each new point cannot be closer to an existing point than this distance. this
  // prevents successive point matchings from creating duplicates
  int pointSeparation;

  // each point is limited in extent to this maximum width and height, in pixels, since
  // otherwise time is wasted (by n-squared searches) looking at huge areas that could
  // not possibly be acceptable sample points
  int pointSize;

  // each matched point is either accepted or rejected. candidate point is the remaining 
  // unmarked point with the highest correlation
  Color acceptedColor;
  Color rejectedColor;
  Color candidateColor;
};

// match points separation minimums
const int PointMatchSeparationMin = 5;
const int PointMatchSizeMin = 4;

struct PointMatchTriplet
{
  // screen coordinates of created point
  int x;
  int y;

  // correlation of sample point with pixels around this created point
  double correlation;
};

// discretize settings determine how colors are used to discretize the image
enum DiscretizeMethod
{
  DiscretizeNone,
  DiscretizeIntensity,
  DiscretizeForeground,
  DiscretizeHue,
  DiscretizeSaturation,
  DiscretizeValue
};

struct DiscretizeSettings
{
  DiscretizeMethod discretizeMethod;

  // low threshold is higher than high threshold when range is union of
  // values below high threshold, and values above low threshold
  int intensityThresholdLow;
  int intensityThresholdHigh;
  int foregroundThresholdLow;
  int foregroundThresholdHigh;
  int hueThresholdLow;
  int hueThresholdHigh;
  int saturationThresholdLow;
  int saturationThresholdHigh;
  int valueThresholdLow;
  int valueThresholdHigh;
};

// hue, saturation and value upper bounds. the lower bounds are all zero. hopefully
// these agree with gimp and other important tools
const int DiscretizeIntensityMax = 100;
const int DiscretizeForegroundMax = 100;
const int DiscretizeHueMax = 360;
const int DiscretizeSaturationMax = 100;
const int DiscretizeValueMax = 100;

// only show the points selected for viewing
enum ViewPointSelection
{
  ViewAxesPoints,
  ViewScalePoints,
  ViewCurvePoints,
  ViewMeasurePoints,
  ViewAllPoints
};
    
// background options
enum BackgroundSelection
{
  BlankBackground, // NoBackground would be a better name but it conflicts with Qt
  OriginalImage,
  ProcessedImage
};

// filter for settings saved between sessions
struct SessionsSettings
{
  bool sessions;
  bool coordinates;
  bool axes;
  bool scaleBar;
  bool curves;
  bool segments;
  bool pointMatch;
  bool measures;
  bool discretize;
  bool gridRemoval;
  bool gridDisplay;
  bool exporting;
  bool viewSelections;

  DigitizeState initialDigitizeState;
};

// run time type identification for points and segment lines. documentation for QCanvasItem
// suggests using values above 1000
const int Rtti_Point = 1000;
const int Rtti_SegmentLine = 1001;

// size of color swatches in curve and measure comboboxes in pixels
const int ComboboxSwatchSize = 12;

// return curve delimiter
QString delimiter(ExportDelimiters del);

// initialize globals
extern void initGlobals(void);

// map our coordinates description into the mmsubs coordinate description
extern mmUnits mmUnitize(CoordSettings coord);

#endif // DIGITDEF_H
