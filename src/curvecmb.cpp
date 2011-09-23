/***************************************************************************
                          curvecmb.cpp  -  description
                             -------------------
    begin                : Thu Oct 31 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: curvecmb.cpp,v $
    Revision 1.4  2006/12/26 07:22:38  markmitch
    Select from default only when there is no selection

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.11  2004/10/07 07:55:47  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.10  2004/10/05 04:00:48  markmitch
    Combobox color reflects digitize state

    Revision 1.9  2004/09/30 05:57:57  markmitch
    Fix file save on close. Better context sensitive help

    Revision 1.8  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.6  2004/09/12 22:29:20  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.5  2003/12/29 06:55:10  markmitch
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

#include <qstringlist.h>


#include "curvecmb.h"
#include "digitview.h"
#include "digitdebug.h"
#include "main.h"
#include "pointsetstyles.h"
#include "defaultsettings.h"
#include <QWhatsThis>

CurveCmb::CurveCmb(QWidget* parent) :
  QComboBox(true, parent, "curve list")
{
  DigitDebug::ctor(QString("curvecmb ") + QString::number((ulong) this, 16));

  setMinimumWidth(DefaultSettings::instance().getComboBoxWidthMin());
  
  setEnabled(false);
  setEditable(false);

  QWhatsThis::add(this, QString(tr("Currently active curve\n\n"
    "While in one of the curve digitizing modes (Curve Point, Segment Fill, or Point Match), any "
    "new points will be assigned to this curve\n\n"
    "Another curve may be selected by using the dropdown button")));
  
  // override the default Qt focus policy with the Windows and Motif policy
  setFocusPolicy(Qt::StrongFocus);
}

CurveCmb::~CurveCmb()
{
  DigitDebug::dtor(QString("curvecmb ") + QString::number((ulong) this, 16));
}

void CurveCmb::attachToDocument(DigitDoc* doc)
{
  clear();

  if (doc)
  {
    // show all curves in combobox
    QStringList list;
    doc->curveNames(&list);
    for (QStringList::iterator itr = list.begin(); itr != list.end(); ++itr)
      insertItem(doc->curveThumbnail(*itr), *itr);

    DigitDebug::curvecmb(QString("attaching to document with ") +
      QString::number(list.count()) + QString(" curves: ") + list.join(QString(" ")));
  }
  else
    DigitDebug::curvecmb(QString("attaching to null document"));
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void CurveCmb::slotComboCurve(bool toggle)
{
  if (toggle)
  {
    setEnabled(true);

    if (currentText().isEmpty())
    {
      for (int index = 0; index < count(); index++)
      {
        if (text(index) == DefaultCurveName)
        {
          setCurrentItem(index);
          break;
        }
      }
    }
  }
}

void CurveCmb::slotComboNotCurve(bool toggle)
{
  if (toggle)
    setEnabled(false);
}
