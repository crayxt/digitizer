/***************************************************************************
                          main.h  -  description
                             -------------------
    begin                : Sun Nov 2 2003
    copyright            : (C) 2003 by 
    email                : mmdigitizer@earthlink.net
    $Log: main.h,v $
    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.5  2004/11/13 04:23:38  markmitch
    Sun Forte changes

    Revision 1.4  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.2  2003/11/03 04:49:14  markmitch
    Missing cvs tag


 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef MAIN_H
#define MAIN_H

// const is needed to pass around __FILE__ in most compilers, but it disagrees with Sun Forte compiler
#ifdef __SUNPRO_CC
#define ENGAUGE_CONST_MODIFIER
#else
#define ENGAUGE_CONST_MODIFIER const
#endif

#define ASSERT_ENGAUGE(a) assert_engauge(a,__FILE__,__LINE__)
#define CHECK_PTR_ENGAUGE(a) check_ptr_engauge((const char*) a,__FILE__,__LINE__)
#define FATAL_ENGAUGE(a) fatal_engauge((const char*) a,__FILE__,__LINE__)

void assert_engauge(const bool a, ENGAUGE_CONST_MODIFIER char* file, const int line);
void check_ptr_engauge(const char* a, ENGAUGE_CONST_MODIFIER char* file, const int line);
void fatal_engauge(const char* s, ENGAUGE_CONST_MODIFIER char* file, const int line);

#endif // MAIN_H
