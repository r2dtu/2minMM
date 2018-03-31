/*
 * File: MazeTracker_pseudocode.c
 * Author: David Tu
 * Last Updated: February 3, 2018
 * Description: 
 */

// Keep track of each maze cell.
// CONVENTION: maze_cells[1][2] represents row 2, column 3 (zero-idx)
struct maze_cell maze_cells[GRID_SIZE][GRID_SIZE] = { 0 };

/* Initialize the maze distance grid. */
void initGrid() {

  // Initialize cells for modified floodfill algorithm
  int curr_dist = GRID_SIZE - 2;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      maze_cells[i][j].dist = curr_dist;
      if (j < GRID_SIZE / 2 - 1) {
        curr_dist -= 1;
      } else if (j > GRID_SIZE / 2 - 1) {
        curr_dist += 1;
      }
//      printf("%d ", maze_cells[i][j].dist);
    }

    // Handle the middle and ends
    if (i < GRID_SIZE / 2 - 1) {
      curr_dist -= 2;
    } else if (i == GRID_SIZE / 2 - 1) {
      curr_dist -= 1;
    }
  }
}

/* Check for surrounding walls and update the maze_cells grid. */
void checkForWalls(int x, int y) {

  /* If a wall detected from any sensor, record it */
  if (detectNorthWall()) {
    maze_cells[x][y].n = 1;

    // Set top cell's south to 1
    maze_cells[x][y + 1].s = 1;
  }

  if (detectEastWall()) {
    maze_cells[x][y].e = 1;

    // Set right cell's west to 1
    maze_cells[x + 1][y].w = 1;
  }

  if (detectSouthWall()) {
    maze_cells[x][y].s = 1;

    // Set bottom cell's north to 1
    maze_cells[x][y - 1].n = 1;
  }

  if (detectWestWall()) {
    maze_cells[x][y].w = 1;

    // Set left cell's east to 1
    maze_cells[x - 1][y].e = 1;
  }
}

/* Determines minimum distance of neighboring open cells */
int getMinNeighborDist(int x, int y) {
  int min = INT_MAX;
  struct maze_cell cell = maze_cells[x][y];
  int nd;
 
  if (!cell.n) {
    min = maze_cells[x][y + 1].dist;
  }
  if (!cell.e) {
    nd = maze_cells[x + 1][y].dist;
    min = nd < min ? nd : min;
  }
  if (!cell.s) {
    nd = maze_cells[x][y - 1].dist;
    min = nd < min ? nd : min;
  }
  if (!cell.w) {
    nd = maze_cells[x - 1][y].dist;
    min = nd < min ? nd : min;
  }

  return min;
}

void MFF(int x, int y) {

  // FF cell stack
  int ff_stack[GRID_SIZE * GRID_SIZE][2];
  int ff_counter = 0;

  /* MFF Algorithm: 
   * 1. Push current cell location onto the stack.
   * 2. While the stack is not empty:
   *      Pop cell location from the stack.
   *      If the minimum dist of neighboring OPEN cells md ≠ curr_cell distance - 1,
   *        Replace curr_cell distance with md + 1, and push ALL neighboring locations onto stack (except center)
   */
  ff_stack[ff_counter][0] = x;
  ff_stack[ff_counter][1] = y;

  while (ff_counter > -1) {

    x = ff_stack[ff_counter][0];
    y = ff_stack[ff_counter][1];
    ff_counter -= 1;

    int md = getMinNeighborDist(x, y);

    if (md != maze_cells[x][y].dist - 1) {

      maze_cells[x][y].dist += 1;

      ff_stack[ff_counter][0] = x - 1;
      ff_stack[ff_counter][1] = y;
      ff_counter += 1;

      ff_stack[ff_counter][0] = x + 1;
      ff_stack[ff_counter][1] = y;
      ff_counter += 1;

      ff_stack[ff_counter][0] = x;
      ff_stack[ff_counter][1] = y - 1;
      ff_counter += 1;

      ff_stack[ff_counter][0] = x;
      ff_stack[ff_counter][1] = y + 1;
      ff_counter += 1;
    }
  }
}

/* Get to the center. */
void findCenter() {

  // Initialize cells for modified floodfill algorithm
  initGrid();

  // Initialize starting position
  Orientation ori = NORTH;
  char currX = 0;
  char currY = 0;
  maze_cells[currX][currY].visited = true;

  /* Keeping looping while we're not at the center */
  while (maze_cells[currX][currY].dist != 0) {

    /* Check current cell for walls */
    checkForWalls(currX, currY);

    /* Perform Modified Floodfill Algorithm */
    MFF(currX, currY);

    /* Move to next cell */
    int part = getPartition(currX, currY);
    PartitionRule rule = nextCellStrategy(part, ori);
    Orientation dir = moveMouse(rule, ori);

    /* Update current mouse position */
    switch (dir) {
      case NORTH:
        currY += 1;
        break;
      case EAST:
        currX += 1;
        break;
      case SOUTH:
        currY -= 1;
        break;
      case WEST:
        currX -= 1;
        break;
    }
  }
}

/* Once center of maze is found, proceed to floodfill */

/*** FLOODFILL ALGORITHM ***/
// see YouTube video for how this works


// Write shortest path to file to remember for next iteration!
