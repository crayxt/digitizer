/***************************************************************************
                          measurecmb.cpp  -  description
                             -------------------
    begin                : Thu Oct 31 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: measurecmb.cpp,v $
    Revision 1.4  2006/12/26 07:22:38  markmitch
    Select from default only when there is no selection

    Revision 1.3  2005/03/20 01:47:06  markmitch
    After KDevelop 3 restructuring

    Revision 1.11  2004/10/07 07:55:48  markmitch
    Thumbnails and tooltips in comboboxes

    Revision 1.10  2004/10/05 04:00:55  markmitch
    Combobox color reflects digitize state

    Revision 1.9  2004/09/30 05:57:57  markmitch
    Fix file save on close. Better context sensitive help

    Revision 1.8  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.6  2004/09/12 22:29:21  markmitch
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
#include <QWhatsThis>

#include "measurecmb.h"
#include "digitview.h"
#include "digitdebug.h"
#include "main.h"
#include "defaultsettings.h"

MeasureCmb::MeasureCmb(QWidget* parent) :
  QComboBox(true, parent, "measure list")
{
  DigitDebug::ctor(QString("measurecmb ") + QString::number((ulong) this, 16));

  setMinimumWidth(DefaultSettings::instance().getComboBoxWidthMin());

  setEnabled(false);
  setEditable(false);

  QWhatsThis::add(this, QString(tr("Currently active measure\n\n"
    "While in the Measure Point measure digitizing mode, any new points will be assigned to this measure\n\n"
    "Another measure may be selected by using the dropdown button")));

  // override the default Qt focus policy with the Windows and Motif policy
  setFocusPolicy(Qt::StrongFocus);
}

MeasureCmb::~MeasureCmb()
{
  DigitDebug::dtor(QString("measurecmb ") + QString::number((ulong) this, 16));
}

void MeasureCmb::attachToDocument(DigitDoc* doc)
{
  clear();

  if (doc)
  {
    // show all measures in combobox
    QStringList list;
    doc->measureNames(&list);
    for (QStringList::iterator itr = list.begin(); itr != list.end(); ++itr)
      insertItem(doc->measureThumbnail(*itr), *itr);

    DigitDebug::measurecmb(QString("attaching to document with ") +
      QString::number(list.count()) + QString(" measures: ") + list.join(QString(" ")));
  }
  else
    DigitDebug::measurecmb(QString("attaching to null document"));
}

/////////////////////////////////////////////////////////////////////
// SLOT IMPLEMENTATION
/////////////////////////////////////////////////////////////////////

void MeasureCmb::slotComboMeasure(bool toggle)
{
  if (toggle)
  {
    setEnabled(true);

    if (currentText().isEmpty())
    {
      for (int index = 0; index < count(); index++)
      {
        if (text(index) == DefaultMeasureName)
        {
          setCurrentItem(index);
          break;
        }
      }
    }
  }
}

void MeasureCmb::slotComboNotMeasure(bool toggle)
{
  if (toggle)
    setEnabled(false);
}
