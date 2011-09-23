/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : Tue Oct 29 14:43:44 PST 2002
    copyright            : (C) 2002 by 
    email                : mmdigitizer@earthlink.net
    $Log: main.cpp,v $
    Revision 1.7  2006/12/28 08:08:40  markmitch
    New command line option to open document

    Revision 1.6  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3.2.4  2006/09/24 06:07:15  markmitch
    New date/time converter

    Revision 1.3.2.3  2006/03/07 06:13:45  markmitch
    Version 2.14. Help window buttons visible. Lazy segment scanning

    Revision 1.3.2.2  2006/03/03 07:36:35  markmitch
    Merge newer documentation into NO_UNDO branch

    Revision 1.3.2.1  2006/03/03 07:06:00  markmitch
    New NO_UNDO branch. Gcc 4 changes for Ubuntu. No more invoke

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.27  2004/11/13 04:23:38  markmitch
    Sun Forte changes

    Revision 1.26  2004/11/11 06:22:18  markmitch
    Pathological case on Mac computer

    Revision 1.25  2004/11/09 06:48:32  markmitch
    Debugging for OSX port

    Revision 1.24  2004/11/07 18:50:16  markmitch
    OSX subroutines

    Revision 1.23  2004/11/07 17:07:54  markmitch
    Connect to plugins

    Revision 1.22  2004/11/06 05:38:10  markmitch
    Consolidate -xbottom and -yleft into -axes

    Revision 1.21  2004/10/28 04:54:32  markmitch
    Scan for axes

    Revision 1.20  2004/10/25 23:55:15  markmitch
    Export command line option. Select initial state

    Revision 1.19  2004/10/05 03:59:54  markmitch
    Remove fprintf

    Revision 1.18  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.16  2004/09/22 06:42:00  markmitch
    Settings can be saved in text file in Windows

    Revision 1.15  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.14  2004/09/12 04:52:14  markmitch
    Most settings are saved. Command line usage in Windows

    Revision 1.13  2004/09/11 05:59:18  markmitch
    First phase of settings archival

    Revision 1.12  2004/09/09 05:33:45  markmitch
    Invoker in work. Windows upgrade to 3.3.3

    Revision 1.11  2004/03/19 00:21:48  markmitch
    Import filter for -onlybmp mode

    Revision 1.10  2004/03/18 16:55:23  markmitch
    Can read bmp files in Simplified Chinese Windows

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

#include <qapplication.h>
#include <qfont.h>
#include <qmessagebox.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qtranslator.h>

#include <stdio.h>
#include <stdlib.h>

#include "digitmain.h"
#include "clipboard.h"
#include "pointsetstyles.h"
#include "digitdef.h"
#include "digitdebug.h"
#include "main.h"
#include "defaultsettings.h"

// command line options. static variables are local and others are global
static QString cmdImport;
static QString cmdExport;
static QString cmdOpen;
QDir cmdManualDirectory;
bool cmdLazySegments;
bool cmdOnlyBmp;
bool cmdPixels;
bool cmdSettingsReset;
bool cmdSettingsText;
static bool cmdXYAxes;
static double cmdXMinG; // x range min in graph units
static double cmdXMaxG; // x range max in graph units
static double cmdYMinG; // y range min in graph units
static double cmdYMaxG; // y range max in graph units

void parseCmdLine(int argc, char *argv[]);
bool parseRangePair(QString arg1, QString arg2,
  double &rangeMin, double &rangeMax);
void showAllUsageAndQuit(bool showAsError);
void showAndQuit(QString msgOutput, bool showAsError);
void showAxisUsageAndQuit();

void assert_engauge(bool condition, ENGAUGE_CONST_MODIFIER char *file, const int line)
{
  if (!condition)
  {
    QMessageBox::critical(0, "Engauge Digitizer",
      QObject::tr("Unexpected problem in %1 at line %2\n")
        .arg(file)
        .arg(line) +
        "Please contact the author at mmdigitizer@earthlink.net with this information");
    exit(-1);
  }
}

void check_ptr_engauge(const char *ptr, ENGAUGE_CONST_MODIFIER char *file, const int line)
{
  if (ptr == 0)
  {
    QMessageBox::critical(0, "Engauge Digitizer",
      QObject::tr("Out of memory in %1 at line %2\n")
        .arg(file)
        .arg(line) +
        "Please contact the author at mmdigitizer@earthlink.net with this information");
    exit(-1);
  }
}

void fatal_engauge(const char *comment, ENGAUGE_CONST_MODIFIER char *file, const int line)
{
  QMessageBox::critical(0, "Engauge Digitizer",
    QObject::tr("Fatal error in %1 at line %2\n")
    .arg(file)
    .arg(line) +
    "\nThe description is '" + comment + "'\n" +
    "Please contact the author at mmdigitizer@earthlink.net with this information");
  exit(-1);
}

int main(int argc, char *argv[])
{
  QApplication app(argc, argv);

#ifdef Q_OS_MACX
  // connect to plugins directory
  app.setLibraryPaths(app.applicationDirPath() + "/../PlugIns");
#endif

  parseCmdLine(argc, argv);

  initGlobals();
  Clipboard::create();
  PointSetStyles::create();
  DefaultSettings::create();

  DefaultSettings& rSettings = DefaultSettings::instance();
  if (rSettings.getWindowMainFontOverride())
  {
    app.setFont(QFont(rSettings.getWindowMainFontName(),
      rSettings.getWindowMainFontSize()));
  }

  QTranslator tor (0);
  // set the location where your .qm files are in load() below as the last parameter instead of "."
  // for development, use "/" to use the english original as
  // .qm files are stored in the base project directory.
  tor.load (QString("digitizer.") + QTextCodec::locale(), ".");
  app.installTranslator (&tor);

  DigitMain digitizer(cmdExport);
  qApp->setMainWidget(&digitizer);

  digitizer.show();

  if (!cmdImport.isEmpty())
	{
    if (cmdXYAxes)
		{
      digitizer.importImageFile(cmdImport, cmdXMinG, cmdXMaxG, cmdYMinG, cmdYMaxG);
		}
    else
		{
      digitizer.importImageFile(cmdImport);
		}
	}

  if (!cmdOpen.isEmpty())
    digitizer.openDocumentFile (cmdOpen);

  return app.exec();
}

void parseCmdLine(int argc, char *argv[])
{
  cmdImport = "";
  cmdExport = "";
  cmdOpen = "";
  cmdManualDirectory = "";
  cmdLazySegments = false;
  cmdOnlyBmp = false;
  cmdPixels = false;
  cmdSettingsReset = false;
  cmdSettingsText = false;
  cmdXYAxes = false;

  bool success = true;
  bool usage = false;

  // QApplication constructor documentation describes the qt built-in command line
  // arguments. we will parse our own debug flags
  for (int i = 1; i < argc; i++)
  {
    QString arg(argv [i]);

    if ((arg == QString("-import")) && (i + 1 < argc))
    {
      cmdImport = argv [i + 1];
      ++i;
    }
    else if ((arg == QString("-export")) && (i + 1 < argc))
    {
      cmdExport = argv [i + 1];
      ++i;
    }
    else if ((arg == QString("-open")) && (i + 1 < argc))
    {
      cmdOpen = argv [i + 1];
      ++i;
    }
    else if (QFile::exists(arg))
    {
      cmdOpen = arg;
    }
    else if (arg == QString("-help"))
      usage = true;
    else if ((arg == QString("-manual")) && (i + 1 < argc))
    {
      cmdManualDirectory = argv [i + 1];
      if (!cmdManualDirectory.exists())
      {
        QMessageBox::critical(0, "Engauge Digitizer",
          QObject::tr("User manual directory %1 does not exist")
            .arg(cmdManualDirectory.path()));
        success = false;
      }
      ++i;
    }
    else if (arg == QString("-onlybmp"))
      cmdOnlyBmp = true;
    else if (arg == QString("-lazysegments"))
      cmdLazySegments = true;
    else if (arg == QString("-pixels"))
      cmdPixels = true;
    else if (arg == QString("-reset"))
      cmdSettingsReset = true;
    else if (arg == QString("-text"))
      cmdSettingsText = true;
    else if ((arg == QString("-axes")) && (i + 4 < argc))
    {
      if (parseRangePair(QString(argv [i + 1]), QString(argv [i + 2]), cmdXMinG, cmdXMaxG) &&
        parseRangePair(QString(argv [i + 3]), QString(argv [i + 4]), cmdYMinG, cmdYMaxG))
        cmdXYAxes = true;
      else
        success = false;

      i += 4;
    }
    else if ((arg == QString("-nograb")) ||
             (arg == QString("-dograb")) ||
             (arg == QString("-sync")))
    {
       // ignore these Qt command line debug options. They will be 
       // processed by QApplication if it was compiled with debugging
    }
    else if (!DigitDebug::setDebugFlag (QString (argv [i])))
      success = false;
  }

  if (!success)
    showAllUsageAndQuit(true); // show as error
  if (usage)
    showAllUsageAndQuit(false); // show as information

  if (cmdXYAxes && cmdImport.isEmpty())
    showAxisUsageAndQuit();
}

bool parseRangePair(QString arg1, QString arg2,
  double &rangeMin, double &rangeMax)
{
  bool okArg1, okArg2;

  rangeMin = arg1.toDouble(&okArg1);
  rangeMax = arg2.toDouble(&okArg2);

  return okArg1 && okArg2;
}

void showAllUsageAndQuit(bool showAsError)
{
  QString msgOutput;

  // display one line with all options unadorned
  msgOutput += QObject::tr(
    "\nUsage:\nengauge [-import FILE] [-export FILE] [-open FILE] [FILE] [-help] [-manual DIRECTORY]\n"
    "[-axes XMIN XMAX YMIN YMAX] [-reset] [-text] [-lazysegments] [-onlybmp] [-pixels]\n%1\n")
    .arg(DigitDebug::usageShort().latin1());

  // display multiple lines with each line having the details of one option
  msgOutput += QObject::tr("\nStartup:\n");
  msgOutput += QObject::tr("[-import FILE] import image file at startup\n");
  msgOutput += QObject::tr("[-open FILE] open document file at startup\n");
  msgOutput += QObject::tr("[FILE] open document file at startup\n");
  msgOutput += QObject::tr("[-help] display this help and exit\n");
  msgOutput += QObject::tr("[-manual DIRECTORY] look for the user manual in the specified directory\n");
  msgOutput += QObject::tr("[-axes XMIN XMAX YMIN YMAX] digitize axis points while importing file\n");
  msgOutput += QObject::tr("[-lazysegments] postpone scanning for segments during startup until needed later\n");
  msgOutput += QObject::tr("\nShutdown:\n");
  msgOutput += QObject::tr("[-export FILE] export active document at shutdown\n");
  msgOutput += QObject::tr("\nSettings:\n");
  msgOutput += QObject::tr("[-reset] reset settings to factory defaults\n");
  msgOutput += QObject::tr("[-text] load and save settings in a text file rather than the registry (Windows only)\n");
  msgOutput += QObject::tr("\nInternationalization:\n");
  msgOutput += QObject::tr("[-onlybmp] import all images as bmp files (fix for Chinese Windows)\n");
  msgOutput += QObject::tr("\nDebugging:\n");
  msgOutput += QObject::tr("[-pixels] track cursor in pixels\n");
  msgOutput += QObject::tr(DigitDebug::usageLong().latin1());

  // environment variables
  msgOutput += QObject::tr("\nEnvironment variables:\n");
  msgOutput += BrowserEnvironmentVariable + QObject::tr("=command to run browser for date/time converter\n");
  msgOutput += UserManualEnvironmentVariable + QObject::tr("=look for the user manual in the specified directory\n");

  showAndQuit(msgOutput, showAsError);
}

void showAndQuit(QString msgOutput, bool showAsError)
{
  msgOutput += QObject::tr("\n");
  
  // show usage using a messagebox rather than writing to stdout or stderr since console
  // output is suppressed in microsoft windows
  if (showAsError)
    QMessageBox::critical(0, QObject::tr("Engauge Digitizer"), msgOutput);
  else
    QMessageBox::information(0, QObject::tr("Engauge Digitizer"), msgOutput);

  exit(-1);
}

void showAxisUsageAndQuit()
{
  QString msgOutput;

  msgOutput += QObject::tr("Command line option '-axes' requires option '-import'\n");

  showAndQuit(msgOutput, true); // show as error
}
