/********************************************************************/
/*                                                                  */
/*  A1 Part 3: runMaze                                              */
/*                                                                  */
/*  Author1 Name: Kian Dadkhah Shokrollahi                          */
/*      - class/function list/main author or main checker           */
/*  Author2 Name: <name here>                                       */
/*      - class/function list/main author or main checker           */
/*                                                                  */
/********************************************************************/

#include "wall.h"
#include "maze.h"
#include <iostream>

int runMaze(Maze& theMaze, int path[], int startCell, int endCell){
  int count = 0;
  theMaze.mark(startCell);
  if (startCell == endCell) {
    count = 1;
    path[count-1] = startCell;
    return count;
  }

  if (!theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1)) &&  !theMaze.isMarked(endCell) && theMaze.canGo(startCell, theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1)))
  {
    count = runMaze(theMaze, path, theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1), endCell);
    if (count > 0)
    {
      path[count] = startCell;
      theMaze.unMark(startCell);
      
      if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell))) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell)))))
      {
        int n = count;
        for (int i = 0; i < n; i++, n--)
        {
          int tempPath = path[i];
          path[i] = path[n];
          path[n] = tempPath;
        }
      }
      return ++count;
    }
  }
  if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell)))) && theMaze.canGo(startCell, theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell))) && !(theMaze.isMarked(endCell)))
  {
    count = runMaze(theMaze, path, theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell)), endCell);
    if (count > 0)
    {
      path[count] = startCell;
      theMaze.unMark(startCell);
      
      if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell))) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell)))))
      {
        int n = count;
        for (int i = 0; i < n; i++, n--)
        {
          int tempPath = path[i];
          path[i] = path[n];
          path[n] = tempPath;
        }
      }
      return ++count;
    }
  }
  if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1))) && theMaze.canGo(startCell, theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1)) && !(theMaze.isMarked(endCell)))
  {
    count = runMaze(theMaze, path, theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1), endCell);
    if (count > 0)
    {
      path[count] = startCell;
      theMaze.unMark(startCell);

      if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell))) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell)))))
      {
        int n = count;
        for (int i = 0; i < n; i++, n--)
        {
          int tempPath = path[i];
          path[i] = path[n];
          path[n] = tempPath;
        }
      }
      
      return ++count;
    }
  }
  if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell)))) && theMaze.canGo(startCell, theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell))) && !(theMaze.isMarked(endCell)))
  {
    count = runMaze(theMaze, path, theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell)), endCell);
    if (count > 0)
    {
      path[count] = startCell;
      theMaze.unMark(startCell);

      if (!(theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) + 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) - 1, theMaze.getCol(startCell))) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell), theMaze.getCol(startCell) - 1)) || theMaze.isMarked(theMaze.getCell(theMaze.getRow(startCell) + 1, theMaze.getCol(startCell)))))
      {
        int n = count;
        for (int i = 0; i < n; i++, n--)
        {
          int tempPath = path[i];
          path[i] = path[n];
          path[n] = tempPath;
        }
      }
      return ++count;
    }
  }
  theMaze.unMark(startCell);
  
  return count;
}
