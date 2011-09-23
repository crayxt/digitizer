/***************************************************************************
                          gridremovaldlg.h  -  description
                             -------------------
    begin                : Fri Dec 5 2003
    copyright            : (C) 2003 by 
    email                : mmdigitizer@earthlink.net
    $Log: gridremovaldlg.h,v $
    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.12  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.10  2004/01/20 05:48:53  markmitch
    Instantaneous response in dialogs

    Revision 1.9  2004/01/04 08:41:00  markmitch
    Dialog for point match settings

    Revision 1.8  2004/01/01 03:52:41  markmitch
    Document stores QImage for speed

    Revision 1.7  2003/12/30 09:14:33  markmitch
    Color chooser has two formats and can be disabled

    Revision 1.6  2003/12/29 06:55:10  markmitch
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

#ifndef GRIDREMOVALDLG_H
#define GRIDREMOVALDLG_H

#include <qdialog.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <q3groupbox.h>
#include <qlineedit.h>
#include <qstring.h>
#include <qvalidator.h>
#include <q3canvas.h>
#include <qcheckbox.h>
//Added by qt3to4:
#include <QMouseEvent>

#include "digitdef.h"
#include "gridremoval.h"

#include "colorchooser.h"

class DigitDoc;
class Transform;

// this dialog box class edits the document's grid removal information, and
// returns an image consisting of the original image with gridline pixels
// removed (for later use by Segments)
class GridRemovalDlg : public QDialog
{
  Q_OBJECT
  
  public:
  
    GridRemovalDlg(QString title, const QImage* imageOriginal,
      const Transform* transform, CoordSettings* coordSettings,
      GridRemovalSettings* gridSettings);
    ~GridRemovalDlg();

    // set color to the color of the pixel selected with the eyedropper
    void setColor(QPoint p);

  public slots:

    void slotLimitChange(bool lower, int limit);
    void slotColorToggled(bool);
    void slotGap(const QString &);
    void slotGridlines();
    void slotGridToggled(bool);
    void slotGridDistance(const QString &);
    void slotThinThickness(const QString &);
    void slotThinToggled(bool);
    void slotWhat(void);

  private:

    // enable or disable color chooser
    void enableColorChooser(bool enable);
  
    // enable or disable buttons as appropriate
    void toggleActions(void);

    // load eyedropper override cursor
    void loadEyedropper(void);

    // convert original image into pixel-addressable QImage
    void loadWorkingImage(void);
    void loadWorkingImageAndIsolateBackground(void);

    QString title;
    const QImage* imageOriginal;
    const Transform* transform;
    CoordSettings* coordSettings;
    GridRemovalSettings* gridSettings;

    // color
    QCheckBox* checkColor;
    QLabel* labelColorMain;
    QLabel* labelColor;
    ColorChooser* colorChooser;

    // gridlines
    QCheckBox* checkGrid;
    QLabel* labelGridMain;
    QLabel* labelGridMesh;
    QPushButton* buttonGridMesh;
    QLabel* labelGridDistance;
    QLineEdit* editGridDistance;
    QDoubleValidator* validatorGridDistance;

    // thin lines
    QCheckBox* checkThin;
    QLabel* labelThinMain;
    QLabel* labelThinThickness;
    QLineEdit* editThinThickness;
    QDoubleValidator* validatorThinThickness;

    // gap
    QLabel* labelGap;
    QLineEdit* editGap;
    QDoubleValidator* validatorGap;

    class ClickablePreview : public Q3CanvasView
    {
      public:
        ClickablePreview(Q3Canvas* canvas, GridRemovalDlg* dlg);
        
        void contentsMousePressEvent(QMouseEvent* e);
        
      private:
        GridRemovalDlg* dlg;
    };
        
    // widgets for previewing the gridline removal results
    QLabel* labelPreview;
    Q3Canvas* previewCanvas;
    ClickablePreview* previewCanvasView;
    
    // navigation buttons
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* buttonWhat;

    // background color is automatically isolated out of original image
    QColor m_backgroundColor;
  
    // color eyedropper
    QCursor* m_cursorEyedropper;

    // store pixel-addressable QImage
    QImage m_imageWorking;
    
    // removeAndConnect function of GridRemoval object takes a fifth of a second to complete,
    // so that function is reentrant with new calls aborting previous calls
    GridRemoval m_gridRemoval;
};

#endif // GRIDREMOVALDLG_H
