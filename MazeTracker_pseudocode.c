/*
 * File: MazeTracker_pseudocode.c
 * Author: David Tu
 * Last Updated: February 3, 2018
 * Description: 
 */

/* 16x16 maze, ea 18cm x 18cm 
 * - each square will be represented by 5 values: 4 for walls and 1 for
 * traversed boolean
 */
struct maze_cell {
  char n;
  char e;
  char s;
  char w;
  bool visited;
  short dist_from_center;
};

// Keep track of each maze cell.
struct maze_cell maze_cells[GRID_SIZE][GRID_SIZE] = { 0 };

// FF cell stack
int ff_stack[GRID_SIZE * GRID_SIZE][2];
int ff_counter;

void findCenter() {

  // Initialize cells for modified floodfill algorithm
  int curr_dist = GRID_SIZE - 2;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      maze_cells[i][j] = curr_dist;
      if (j < GRID_SIZE / 2 - 1) {
        curr_dist -= 1;
      } else if (j > GRID_SIZE / 2 - 1) {
        curr_dist += 1;
      }
      printf("%d ", maze_cells[i][j]);
    }
    if (i < GRID_SIZE / 2 - 1) {
      curr_dist -= 2;
    } else if (i == GRID_SIZE / 2 - 1) {
      curr_dist -= 1;
    }
  }

  // NESW changes with mouse orientation
  char orientation = 0;
  char currX = 0;
  char currY = 0;

  /* Check current cell for walls */
  /* If detected a wall from any sensor, record it */
  if (detectNorthWall()) {
    maze_cells[currX][currY].n = 1;

    // Set top cell's south to 1
    maze_cells[currX][currY + 1].s = 1;
  }

  if (detectEastWall()) {
    maze_cells[currX][currY].e = 1;

    // Set right cell's west to 1
    maze_cells[currX + 1][currY].w = 1;
  }

  if (detectSouthWall()) {
    maze_cells[currX][currY].s = 1;

    // Set bottom cell's north to 1
    maze_cells[currX][currY - 1].n = 1;
  }

  if (detectWestWall()) {
    maze_cells[currX][currY].w = 1;

    // Set left cell's east to 1
    maze_cells[currX - 1][currY].e = 1;
  }

  /* Begin Depth-first search */
  /* If wall is not detected, go that direction. Priority: t, r, b, l */
  /* TODO PRIORITY CHANGES WITH WHICH PARTITION THE MOUSE IS IN */
  maze_cells[currX][currY].visited = true;

  /* Continue DFS until center of the maze is found */
  /* Actually, we're going to implement a modified flood-fill algorithm
   * (essentially kind of using DFS/BFS) */
  /* MFF Algorithm: 
   * 1. Push current cell location onto the stack.
   * 2. While the stack is not empty:
   *      Pull next cell location from the stack
   *      If the minimum dist of neighboring OPEN cells md ≠ curr_cell distance - 1,
   *        Replace curr_cell distance with md + 1, and push ALL neighboring locations onto stack (except center)
   */
  /*
   * While curr_cell dist != 0:
   *    Move to next cell.
   *    MFF().
   *    Move to next cell based on prioritized direction.
   */
}

/* Once center of maze is found, proceed to floodfill */

/*** FLOODFILL ALGORITHM ***/
// see YouTube video for how this works

