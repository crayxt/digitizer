/***************************************************************************
                          digitdebug.h  -  description
                             -------------------
    begin                : Tue Dec 3 2002
    copyright            : (C) 2002 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: digitdebug.h,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.8  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.6  2004/09/12 04:52:14  markmitch
    Most settings are saved. Command line usage in Windows

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

#ifndef DIGITDEBUG_H
#define DIGITDEBUG_H

#include <qstring.h>

// this completely static class filters and formats debug information. for
// debug there is also the Key_D button which tells DigitMain to dump the
// document
class DigitDebug
{
  public:
  
    DigitDebug();
    ~DigitDebug();

    // any changes to the Flags enumeration must be reflected in the
    // debug methods immediately below, and in flagStringsLookup
    enum Flags
    {
      Ctor = 0,
      Dtor,
      CurveCmb,
      MeasureCmb,
      Refresh,
      Scanning,
      MaxFlags
    };

    // debug methods
    static void ctor(QString str)          { genericDebug(Ctor, str); }
    static void dtor(QString str)          { genericDebug(Dtor, str); }
    static void curvecmb(QString str)      { genericDebug(CurveCmb, str); }
    static void measurecmb(QString str)    { genericDebug(MeasureCmb, str); }
    static void refresh(QString str)       { genericDebug(Refresh, str); }
    static void scanning(QString str)      { genericDebug(Scanning, str); }
        
    // documentation of command line options
    static QString usageShort(void);
    static QString usageLong(void);
    
    // if string is one of the command line debug flags, returns true and
    // enables that type of debug spew
    static bool setDebugFlag(QString str);
    
  private:

    enum Lookup
    {
      LookupFlagName, // command line option token (minus leading dash)
      LookupUsageHelp // usage information displayed by -help, or after command line error
    };
    
    // return one of the strings associated with a particular flag. the strings are
    // consolidated into one place so developers will be more likely to keep things in sync
    static QString flagStringsLookup(Flags flag, Lookup lookup);

    // wrappers around flagStringsLookup
    static QString flagName(Flags flag);
    static QString usageHelp(Flags flag);

    // mask that filters the debug spew. each bit represents one type of spew
    static unsigned long debugMask;

    // filter debug lines, format them with common style and output them
    static void genericDebug(Flags flag, QString str);   
};

#endif // DIGITDEBUG_H
