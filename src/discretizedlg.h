/***************************************************************************
                          discretizedlg.h  -  description
                             -------------------
    begin                : Wed Dec 17 2003
    copyright            : (C) 2003 by 
    email                : mmdigitizer@earthlink.net
    $Log: discretizedlg.h,v $
    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.15  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.13  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.12  2004/01/20 05:48:53  markmitch
    Instantaneous response in dialogs

    Revision 1.11  2004/01/04 08:40:59  markmitch
    Dialog for point match settings

    Revision 1.10  2004/01/01 03:52:41  markmitch
    Document stores QImage for speed

    Revision 1.9  2003/12/29 20:51:50  markmitch
    All discretize modes work

    Revision 1.8  2003/12/29 06:55:10  markmitch
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

#ifndef DISCRETIZEDLG_H
#define DISCRETIZEDLG_H

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

#include "digitdef.h"
#include "colorchooser.h"
#include "discretize.h"

// this dialog box class edits the discretizing settings, which determine
// how the original image is discretized
class DiscretizeDlg : public QDialog
{
  Q_OBJECT
  
  public:
  
    DiscretizeDlg(QString title, const QImage* imageOriginal,
      DiscretizeSettings* settings);
    ~DiscretizeDlg();

  public slots:

    void slotIntensity();
    void slotForeground();
    void slotHue();
    void slotLimitChange(bool, int);
    void slotSaturation();
    void slotValue();
    void slotWhat(void);

  private:

    // set discretize method, loading appropriate background histogram image
    void setDiscretizeMethod(DiscretizeMethod method);

    // set individual color attributes
    void setHueHigh(int limit);
    void setHueLow(int limit);
    void setSaturationHigh(int limit);
    void setSaturationLow(int limit);
    void setValueHigh(int limit);
    void setValueLow(int limit);

    // enable or disable buttons as appropriate
    void toggleActions(void);

    QString title;
    const QImage* imageOriginal;
    DiscretizeSettings* settings;
    
    // convert original image into pixel-addressable QImage, using current settings.
    // the first time through this also loads histograms
    void loadWorkingImage(void);
   
    // discretize method selection
    Q3ButtonGroup* groupSelection;

    // discretize methods
    QRadioButton* buttonIntensity;
    QRadioButton* buttonForeground;
    QRadioButton* buttonHue;
    QRadioButton* buttonSaturation;
    QRadioButton* buttonValue;

    // widgets for controlling the color attribute limits
    ColorChooser* colorChooser;
    
    // widgets for previewing the discretize results
    QLabel* labelPreview;
    Q3Canvas* previewCanvas;
    Q3CanvasView* previewCanvasView;
    
    // navigation buttons
    QPushButton* buttonOk;
    QPushButton* buttonCancel;
    QPushButton* buttonWhat;

    // store pixel-addressable QImage
    QImage imageWorking;

    // discretize function of Discretize object takes a fifth of a second to complete,
    // so that function is reentrant with new calls aborting previous calls
    Discretize discretize;
};

#endif // DISCRETIZEDLG_H
