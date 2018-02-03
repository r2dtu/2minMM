/*
 * File: floodfill.c
 * Author: Clark Phan & David Tu
 * Last Updated: February 3, 2018
 * Description: Flood-fill algorithm implementation to find the shortest path
 *              from the center of the maze to the start.
 *
 * TODO Notes: If we use modified flood-fill and traverse every cell
 * in the maze, is this even necessary anymore?
 */

const int size = 12; // maze size
int maze[size][size]; // stores cell distance values from center

int adj_wallstack[size * size][2] = { 0 }; // stores neighboring cells 
int wall_counter; // counter for knowing position of elements in stack 

int ff_stack[size * size][2]; // main stack
int ff_count; // main stack counter for knowing position

/*
 * Clears the adjacent walls stack.
 */
void clr_wallstack() {
  for (int i = 0; i < size * size; i++) {
    for (int j = 0; j < 2; j++) {
      adj_wallstack[i][j] = 0;
    }
  }
}

/*
 * Initializes the maze grid values to the max distance.
 */
void init_maze() {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
			maze[i][j] = size * size - 1;
    }   
  }
}

/*
 * Stores the adjacent cells on the adj_wallstack.
 */
void addNeighbors(int x, int y) {

  // Check 4 cells. If there's a wall there, don't add it.
  if (maze_cells[x][y].n == 0) {
    adj_wallstack[wall_counter][0] = x;
    adj_wallstack[wall_counter][1] = y + 1;
    wall_counter += 1;
  }
  if (maze_cells[x][y].e == 0) {
    adj_wallstack[wall_counter][0] = x + 1;
    adj_wallstack[wall_counter][1] = y;
    wall_counter += 1;
  }
  if (maze_cells[x][y].s == 0) {
    adj_wallstack[wall_counter][0] = x;
    adj_wallstack[wall_counter][1] = y - 1;
    wall_counter += 1;
  }
  if (maze_cells[x][y].w == 0) {
    adj_wallstack[wall_counter][0] = x - 1;
    adj_wallstack[wall_counter][1] = y;
    wall_counter += 1;
  }

}

/*
 * Floodfill algorithm (no mouse movement).
 */
void floodfill() {

  // Initialize maze grid distances
  init_maze();

  // Keep track of the distance from the center 
  int level = 0;

  // Begin floodfill
  while (true) {

    // Error check
    if (ff_count < 0) {
      break;
    }

    // Initialize the adjacent walls stack
    clr_wallstack();

    /* 
       Repeat until ff_stack is empty:
       1. Remove a cell from ff_stack
       2. If DistanceValue(cell) = 255 {
       Let DistanceValue(cell) = level
       Place all open neighbors of cell into wall stack
       }
     */
    while (ff_count >= 0) {

      // Get the cell's x, y (from the stack)
      int currX = ff_stack[ff_count][0];
      int currY = ff_stack[ff_count][1];

      // Update the distance of the cell
      if (maze[currX][currY] == 255) {

        // Let DistanceValue(cell) = level
        a[currX][currY] = level;

        // Place all open neighbors of cell into wall stack
        addNeighbors(ff_stack[ff_count][0], ff_stack[ff_count][1]);
      }

      // We've finished with that cell, go to next one on the stack
      ff_stack[ff_count][0] = ff_stack[ff_count][1] = 0;
      --ff_count;
    }

    // Pause?

    // Check if wallstack is empty
    if (wall_counter != 0) {

      // If not empty, incrementlevel
      level++;
      while (wall_counter > 0) {

        // Increment ff_count (change position)
        ++ff_count;

        // Let ff_stack = wall stack
        ff_stack[ff_count][0] = adj_wallstack[wall_counter - 1][0];
        ff_stack[ff_count][1] = adj_wallstack[wall_counter - 1][1];
        wall_counter--;
      }

      // Zero out the wallstack
      clr_wallstack();
    }
  }
}

