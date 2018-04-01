#include "maze.h"

/* Initialize the maze distance grid. */
void initGrid(struct mazeCell maze[][]) {

  // Initialize cells for modified floodfill algorithm
  int curr_dist = GRID_SIZE - 2;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      maze[i][j].dist = curr_dist;
      if (j < GRID_SIZE / 2 - 1) {
        curr_dist -= 1;
      } else if (j > GRID_SIZE / 2 - 1) {
        curr_dist += 1;
      }
//      printf("%d ", maze[i][j].dist);
    }

    // Handle the middle and ends
    if (i < GRID_SIZE / 2 - 1) {
      curr_dist -= 2;
    } else if (i == GRID_SIZE / 2 - 1) {
      curr_dist -= 1;
    }
  }
}

int readGrid(struct mazeCell maze[][]) {

  FILE * fp = fopen("maze.gd", "r");
  if (!fp) {
    return 0;
  }

  /* TODO Parse the file into the maze param */
}

void writeGrid(struct mazeCell maze[][]) {
  FILE * fp = fopen("maze.gd", "r+");
  if (fp) {
    /* Delete the file? */
  }

  /* TODO Write the maze grid to the file */
}

/* Check for surrounding walls and update the mazeCells grid. */
void checkForWalls(int x, int y) {

  /* If a wall detected from any sensor, record it */
  if (detectNorthWall()) {
    mazeCells[x][y].n = 1;

    // Set top cell's south to 1
    mazeCells[x][y + 1].s = 1;
  }

  if (detectEastWall()) {
    mazeCells[x][y].e = 1;

    // Set right cell's west to 1
    mazeCells[x + 1][y].w = 1;
  }

  if (detectSouthWall()) {
    mazeCells[x][y].s = 1;

    // Set bottom cell's north to 1
    mazeCells[x][y - 1].n = 1;
  }

  if (detectWestWall()) {
    mazeCells[x][y].w = 1;

    // Set left cell's east to 1
    mazeCells[x - 1][y].e = 1;
  }
}

/* Determines minimum distance of neighboring open cells */
int getMinNeighborDist(int x, int y) {
  int min = INT_MAX;
  struct mazeCell cell = mazeCells[x][y];
  int nd;
 
  if (!cell.n) {
    min = mazeCells[x][y + 1].dist;
  }
  if (!cell.e) {
    nd = mazeCells[x + 1][y].dist;
    min = nd < min ? nd : min;
  }
  if (!cell.s) {
    nd = mazeCells[x][y - 1].dist;
    min = nd < min ? nd : min;
  }
  if (!cell.w) {
    nd = mazeCells[x - 1][y].dist;
    min = nd < min ? nd : min;
  }

  return min;
}

int MFF(int x, int y) {

  // FF cell stack
  int ffStack[GRID_SIZE * GRID_SIZE][2];
  int ffCounter = 0;

  /* MFF Algorithm: 
   * 1. Push current cell location onto the stack.
   * 2. While the stack is not empty:
   *      Pop cell location from the stack.
   *      If the minimum dist of neighboring OPEN cells md ≠ curr_cell distance - 1,
   *        Replace curr_cell distance with md + 1, and push ALL neighboring locations onto stack (except center)
   */
  ffStack[ffCounter][0] = x;
  ffStack[ffCounter][1] = y;
  int retVal = getMinNeighborDist(x, y);

  while (ffCounter > -1) {

    x = ffStack[ffCounter][0];
    y = ffStack[ffCounter][1];
    ffCounter -= 1;

    int md = getMinNeighborDist(x, y);

    if (md != mazeCells[x][y].dist - 1) {

      mazeCells[x][y].dist += 1;

      ffStack[ffCounter][0] = x - 1;
      ffStack[ffCounter][1] = y;
      ffCounter += 1;

      ffStack[ffCounter][0] = x + 1;
      ffStack[ffCounter][1] = y;
      ffCounter += 1;

      ffStack[ffCounter][0] = x;
      ffStack[ffCounter][1] = y - 1;
      ffCounter += 1;

      ffStack[ffCounter][0] = x;
      ffStack[ffCounter][1] = y + 1;
      ffCounter += 1;
    }
  }

  return retVal;
}

/* Get to the center. */
void findCenter(struct mazeCell mazeCells[][], int * retX, int * retY,
                    Orientation * retOri) {

  // Initialize starting position
  Orientation ori = NORTH;
  char currX = 0;
  char currY = 0;
  mazeCells[currX][currY].visited = true;

  /* Keeping looping while we're not at the center */
  while (mazeCells[currX][currY].dist != 0) {

    /* Check current cell for walls */
    checkForWalls(currX, currY);

    /* Perform Modified Floodfill Algorithm */
    int md = MFF(currX, currY);

    /* Move to next cell */
    ori = moveMouse(currX, currY, md, ori);

    /* Update current mouse position */
    switch (ori) {
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

  *retX = currX;
  *retY = currY;
  *retOri = ori;
}

void getOut(struct mazeCell mazeCells[][], int currX, int currY, 
                Orientation ori) {

  /* Keeping looping while we're not at the start */
  while (currX != currY || currX != 0) {

    if (!mazeCells[currX][currY].visited) {

      /* Check current cell for walls */
      checkForWalls(currX, currY);
    }

    /* Perform Modified Floodfill Algorithm */
    MFF(currX, currY);

    /* Move to next cell */
    ori = moveMouse(currX, currY, mazeCells[currX][currY].dist + 1, ori);

    /* Update current mouse position */
    switch (ori) {
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

/* Determines which partition of the maze the mouse is in */
/* Note: comments assume 16x16 maze */
int getPartition(int x, int y, int size) {

  /* x in [0, 6] */
  if (x < size / 2 - 1) {

    /* P-1 */
    if (y < size / 2 - 1) {
      return 1;
    }
    /* P-12 */
    else if (y == size / 2 - 1) {
      return 12;
    }
    /* P-11 */
    else if (y == size / 2) {
      return 11;
    }
    /* P-4 */
    else {
      return 4;
    }
  }

  /* x is 7 */
  else if (x == size / 2 - 1) {

    /* P-5 */
    if (y < size / 2 - 1) {
      return 5;
    }
    /* P-10 */
    else if (y > size / 2) {
      return 10;
    }

    /* Mouse is in the center. This method should not have been called! */
    return -1;
  }

  /* x is 8 */
  else if (x == size / 2) {

    /* P-6 */
    if (y < size / 2 - 1) {
      return 5;
    }
    /* P-9 */
    else if (y > size / 2) {
      return 9;
    }

    /* Mouse is in the center. This method should not have been called! */
    return -1;
  }

  /* x in [9, 15] */
  else {

    /* P-1 */
    if (y < size / 2 - 1) {
      return 2;
    }
    /* P-12 */
    else if (y == size / 2 - 1) {
      return 7;
    }
    /* P-11 */
    else if (y == size / 2) {
      return 8;
    }
    /* P-4 */
    else {
      return 3;
    }
  }
}

/*
 * Determines which direction the mouse should go.
 */
PartitionRule nextCellStrategy(int partition, Orientation ori) {
  switch (partition) {
    case 1:
      switch (ori) {
        case NORTH:
          return CR;
        case EAST:
          return CL;
        case SOUTH:
          return LH;
        case WEST:
          return RH;
      }
    case 2:
      switch (ori) {
        case NORTH:
          return CL;
        case EAST:
          return LH;
        case SOUTH:
          return RH;
        case WEST:
          return CR;
      }
    case 3:
      switch (ori) {
        case NORTH:
          return LH;
        case EAST:
          return RH;
        case SOUTH:
          return CR;
        case WEST:
          return CL;
      }
    case 4:
      switch (ori) {
        case NORTH:
          return RH;
        case EAST:
          return CR;
        case SOUTH:
          return CL;
        case WEST:
          return LH;
      }
    case 5:
      switch (ori) {
        case NORTH:
          return CR;
        case EAST:
        case SOUTH:
          return LH;
        case WEST:
          return RH;
      }
    case 6:
      switch (ori) {
        case NORTH:
          return CL;
        case EAST:
          return LH;
        case SOUTH:
        case WEST:
          return RH;
      }
    case 7:
      switch (ori) {
        case NORTH:
        case EAST:
          return LH;
        case SOUTH:
          return RH;
        case WEST:
          return CR;
      }
    case 8:
      switch (ori) {
        case NORTH:
          return LH;
        case EAST:
        case SOUTH:
          return RH;
        case WEST:
          return CL;
      }
    case 9:
      switch (ori) {
        case NORTH:
        case WEST:
          return LH;
        case EAST:
          return RH;
        case SOUTH:
          return CR;
      }
    case 10:
      switch (ori) {
        case NORTH:
        case EAST:
          return RH;
        case SOUTH:
          return CL;
        case WEST:
          return LH;
      }
    case 11:
      switch (ori) {
        case NORTH:
          return RH;
        case EAST:
          return CR;
        case SOUTH:
        case WEST:
          return LH;
      }
    case 12:
      switch (ori) {
        case NORTH:
        case WEST:
          return RH;
        case EAST:
          return CL;
        case SOUTH:
          return LH;
      }
  }
}

