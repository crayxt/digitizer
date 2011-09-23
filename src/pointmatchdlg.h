/***************************************************************************
                          pointmatchdlg.h  -  description
                             -------------------
    begin                : Thu Jan 1 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: pointmatchdlg.h,v $
    Revision 1.6  2006/12/20 08:20:26  markmitch
    Rework of point matching to handle skipping

    Revision 1.5  2006/10/08 06:41:50  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.7  2004/11/07 06:23:54  markmitch
    Narrow buttons get chopped in OSX

    Revision 1.6  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.4  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.3  2004/01/07 07:48:07  markmitch
    Implementing point match

    Revision 1.2  2004/01/06 08:14:39  markmitch
    Point match mode highlights sample point

    Revision 1.1  2004/01/04 08:41:00  markmitch
    Dialog for point match settings


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef POINTMATCHDLG_H
#define POINTMATCHDLG_H

#include <qdialog.h>
#include <q3buttongroup.h>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <q3groupbox.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qvalidator.h>
#include <q3canvas.h>
#include <qcheckbox.h>
#include <qcombobox.h>

#include "digitdef.h"
#include "discretize.h"
#include "point.h"
#include "pointset.h"

class Highlight;

// one of these modal dialog boxes belongs to each view, and is
// hidden until the user selects "point match" mode. the user
// uses this dialog box to select the sample point to be matched, and
// the number of points that satisfactorily match the sample point.
// the benefits of one PointMatchDlg per DigitView are:
// 1) simpler and more robust code
// 2) user can have different sample points by using multiple DigitViews
class PointMatchDlg : public QDialog
{
  Q_OBJECT
  
  public:
  
    PointMatchDlg(const QString title, PointSetStyle style,
      PointMatchSettings* settings);
    ~PointMatchDlg();

  public slots:

    void slotAcceptedColor(const QString &text);
    void slotCandidateColor(const QString &text);
    void slotPointSeparation(const QString &text);
    void slotPointSize(const QString &text);
    void slotRejectedColor(const QString &text);
    void slotWhat(void);
     
  private:

    enum
    {
      PreviewWidth = 320
    };

    enum
    {
      PreviewHeight = 100
    };
    
    // color pixels in preview image using point image as mask
    void drawPoint(QImage* imagePreview, const QImage &imagePoint,
      int xCenter, int yCenter, const Discretize &discretize, DiscretizeSettings disc);

    // convert editor-friendly xpm files into pixel-addressable masks
    void loadPointImages(void);

    // make points that represent points in original image, and engauge digitizer points
    void makePoints(void);

    // styles must be set before any points are created
    void setPointSetStyles(void);
    
    // enable or disable buttons as appropriate
    void toggleActions(void);
  
    // return true if all settings contraints are currently satisfied
    bool validateSettings(void);

    // update preview after modifying a property
    void updatePreview(void);
    
    QString title;
    PointSetStyle style;
    PointMatchSettings* settings;

    // point match properties
    QLabel* labelPointSeparation;
    QLineEdit* editPointSeparation;
    QIntValidator* validatorPointSeparation;

    QLabel* labelPointSize;
    QLineEdit* editPointSize;
    QIntValidator* validatorPointSize;

    QLabel* labelAcceptedColor;
    QComboBox* comboAcceptedColor;

    QLabel* labelRejectedColor;
    QComboBox* comboRejectedColor;

    QLabel* labelCandidateColor;
    QComboBox* comboCandidateColor;

    // widgets for previewing the point and line styles of the currently selected segment
    QLabel* labelPreview;
    Q3Canvas* previewCanvas;
    Q3CanvasView* previewCanvasView;
    Highlight* highlight;
    PointSet pointsetAccepted, pointsetRejected;

    // navigation buttons
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* buttonWhat;

    // point images for preview window are used as masks to color pixels
    QImage imageDiamond, imageCircle, imageSquare;
};

#endif // POINTMATCHDLG_H
