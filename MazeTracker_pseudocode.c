/* 16x16 maze, ea 18cm x 18cm 
 * - each square will be represented by 5 values: 4 for walls and 1 for
 * traversed boolean
 */
struct maze_cell {
  char t;
  char r;
  char b;
  char l;
  bool visited;
};

struct maze_cell maze_cells[16][16];

struct maze_cell curr_cell;

/* Initialize curr_cell to first cell */
/* Check current cell for walls */
/* If detected a wall from any sensor, record it */

/* Begin Depth-first search */
/* If wall is not detected, go that direction. Priority: t, r, b, l */
/* Keep track of which forks to check using a priority-queue? */

/* Continue DFS until center of the maze is found */
/* Once center of maze is found, proceed to floodfill */

/*** FLOODFILL ALGORITHM ***/
// see YouTube video for how this works


