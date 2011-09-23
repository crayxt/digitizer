/***************************************************************************
                          grid.h  -  description
                             -------------------
    begin                : Tue Nov 19 2002
    copyright            : (C) 2002 by Mark Mitchell
    email                : mmdigitizer@earthlink.net
    $Log: grid.h,v $
    Revision 1.5  2006/10/08 06:41:49  markmitch
    NO_UNDO branch moved to HEAD

    Revision 1.3  2005/03/20 01:47:05  markmitch
    After KDevelop 3 restructuring

    Revision 1.10  2004/09/27 04:52:26  markmitch
    KDevelop does not allow renaming source directory to src

    Revision 1.8  2004/09/12 22:29:21  markmitch
    Settings archival complete. Qt2-compatibility code removed

    Revision 1.7  2003/12/29 06:55:10  markmitch
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

#ifndef GRID_H
#define GRID_H

#include <q3canvas.h>
#include <q3ptrlist.h>

#include "digitdef.h"

class Transform;

// this class owns the grid lines
class Grid
{
  public: 

    Grid(GridType gridType, Q3Canvas* canvas);
    ~Grid();                                                 

    // grid lines are rebuilt after change to any of the arguments of this function. they
    // start out hidden and remain so until showGrid is called
    void makeGridLines(const Transform* transform, const CoordSettings coord,
      const GridMeshSettings grid);

    // turn grid on/off
    bool grid(void) { return m_grid; }
    void showGrid(bool toggle);

  private:

    GridType m_gridType;
    Q3Canvas* m_canvas;

    // pen for gridlines depends on m_gridType, and if line represents R direction
    QPen gridlinePen(bool R);

    // true for visible grid lines, otherwise false for hidden
    bool m_grid;
    
    Q3PtrList<Q3CanvasLine> m_lines;
};

#endif // GRID_H
