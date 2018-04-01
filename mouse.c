/*
 * File: main.c
 * Author: David Tu
 * Last Updated: March 31, 2018
 * Description: Hardware compatible software to physically move the mouse 
 * and read onboard sensors.
 */
#include "Maze.h"

Orientation moveMouse(int x, int y, int newCellDist, Orientation ori) {

  /* Only need to worry about partitions when more than one neighbor cell 
   * has same distance value */
  int part = getPartition(currX, currY);
  PartitionRule rule = nextCellStrategy(part, ori);

  /* Record new calculated position */
  Orientation dir;
  int newX, newY;

  /* Move mouse to neighboring cell with minimum distance */
  struct maze_cell cell = maze_cells[x][y];
  if (!cell.n) {
    if (maze_cells[x][y + 1].dist == newCellDist) {
      newX = x;
      newY = y + 1;
      dir = NORTH;
    }
  }
  if (!cell.e) {
    if (maze_cells[x + 1][y].dist == newCellDist) {
      newX = x + 1;
      newY = y;
      dir = EAST;
    }
  }
  if (!cell.s) {
    if (maze_cells[x][y - 1].dist == newCellDist) {
      newX = x;
      newY = y - 1;
      dir = SOUTH;
  }
  if (!cell.w) {
    if (maze_cells[x - 1][y].dist == newCellDist) {
      newX = x - 1;
      newY = y;
      dir = WEST;
    }
  }
}

void turnMouse() {

}

void readEncoders() {

}

void readIR() {

}

void detectNorthWall() {

}

void detectEastWall() {

}

void detectSouthWall() {

}

void detectWestWall() {

}

