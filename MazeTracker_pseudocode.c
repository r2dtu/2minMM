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
};

struct maze_cell maze_cells[16][16] = { 0 };

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
/* PRIORITY CHANGES WITH WHICH PARTITION THE MOUSE IS IN */
/* Keep track of which forks to check using a priority-queue? */
maze_cells[currX][currY].visited = true;

/* Continue DFS until center of the maze is found */
/* Once center of maze is found, proceed to floodfill */

/*** FLOODFILL ALGORITHM ***/
// see YouTube video for how this works


