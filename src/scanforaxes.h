/***************************************************************************
                          scanforaxes.h  -  description
                             -------------------
    begin                : Tue Oct 26 2004
    copyright            : (C) 2004 by 
    email                : mmdigitizer@earthlink.net
    $Log: scanforaxes.h,v $
    Revision 1.1  2005/03/20 01:47:07  markmitch
    After KDevelop 3 restructuring

    Revision 1.3  2004/11/09 06:44:35  markmitch
    Microsoft compiler bug. Use typedef for consistency

    Revision 1.2  2004/10/29 03:06:13  markmitch
    Scan for axes works up to generating axis points

    Revision 1.1  2004/10/28 04:54:32  markmitch
    Scan for axes


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef SCANFORAXES_H
#define SCANFORAXES_H

#include <q3memarray.h>

#include "digitdoc.h"
#include "digitdebug.h"

typedef Q3MemArray<unsigned int> AxisSlice;

// scan a newly-imported document for the x and y axes, then create
// three axis points
class ScanForAxes
{
  public:

    // ranges for x and y axes in graph coordinates 
    ScanForAxes(double xMinG, double xMaxG, 
      double yMinG, double yMaxG,
      DigitDoc* doc);
    ~ScanForAxes();

    // perform the scanning
    void execute();

  private:

    // scan in either x or y axis
    void scanXAxis(const QImage& img, Q3CanvasLine& scanLine, Q3CanvasLine& bestXLine,
      int& xAxisRow, int& xAxisColMin, int& xAxisColMax);
    void scanYAxis(const QImage& img, Q3CanvasLine& scanLine, Q3CanvasLine& bestYLine,
      int& yAxisCol, int& yAxisRowMin, int& yAxisRowMax);

    // convolutions along axis slice pinpoint start and end of axis line
    void scanAxisForLowEndpoint(AxisSlice axisSlice, int& axisMin);
    void scanAxisForHighEndpoint(AxisSlice axisSlice, int& axisMax);

    // update best lines in active view (there is only one view during import). this
    // is SLOW so only call this when necessary
    void updateView(const QImage& img);

    double m_xMinG;
    double m_xMaxG;
    double m_yMinG;
    double m_yMaxG;
    DigitDoc* m_doc;

};

#endif // SCANFORAXES_H
