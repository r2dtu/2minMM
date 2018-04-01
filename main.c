#include "Maze.h"

// Keep track of each maze cell (global array).
// CONVENTION: mazeCells[1][2] represents row 2, column 3 (zero-idx)
struct maze_cell mazeCells[GRID_SIZE][GRID_SIZE] = { 0 };

int main() {

  int x, y;
  Orientation ori;

  /* Read grid from file */
  int result = readGrid(mazeCells);

  if (!result) {

    // Initialize cells for modified floodfill algorithm
    initGrid(mazeCells);
  }

  /* Once center of maze is found, proceed to floodfill */
  findCenter(mazeCells, &x, &y, &ori);

  /* Just traverse the path, in increasing distance order */
  getOut(mazeCells, x, y, ori);

  /* Write maze grid to file to remember for next iteration */
  writeGrid(mazeCells);
}
