/*
 * File: MazeHelper.cpp
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: Implementation of maze helper functions.
 */

#include "MazeHelper.hpp"
#include "MazeCell.hpp"

/* Initialize the maze distance grid. */
void initGrid(MazeCell maze[][]) {
  
  // Initialize cells for modified floodfill algorithm
  int currDist = GRID_SIZE - 2;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      maze[i][j].setDist(currDist);
      if (j < GRID_SIZE / 2 - 1) {
        currDist -= 1;
      } else if (j > GRID_SIZE / 2 - 1) {
        currDist += 1;
      }
      std::cout << maze[i][j].getDist() << " " << std::endl;
      
      // Figure out which partition the cell is in
      maze[i][j].setPartition(determinePartition(i, j));
    }

    // Handle the middle and ends
    if (i < GRID_SIZE / 2 - 1) {
      currDist -= 2;
    } else if (i == GRID_SIZE / 2 - 1) {
      currDist -= 1;
    }
  }
}

/* Determines which partition a cell is in */
char determinePartition(int x, int y) {

    /* x in [0, 6] */
    if (x < GRID_SIZE / 2 - 1) {

        /* P-1 */
        if (y < GRID_SIZE / 2 - 1) {
            return 1;
        }   
        /* P-12 */
        else if (y == GRID_SIZE / 2 - 1) {
            return 12; 
        }   
        /* P-11 */
        else if (y == GRID_SIZE / 2) {
            return 11; 
        }   
        /* P-4 */
        else {
            return 4;
        }   
    }

    /* x is 7 */
    else if (x == GRID_SIZE / 2 - 1) {

        /* P-5 */
        if (y < GRID_SIZE / 2 - 1) {
            return 5;
        }   
        /* P-10 */
        else if (y > GRID_SIZE / 2) {
            return 10; 
        }   
        
        /* Mouse is in the center. */
        return -1;
    }

    /* x is 8 */
    else if (x == GRID_SIZE / 2) {

        /* P-6 */
        if (y < GRID_SIZE / 2 - 1) {
            return 5;
        }
        /* P-9 */
        else if (y > GRID_SIZE / 2) {
            return 9;
        }
    
        /* Mouse is in the center. */
        return -1;
    }

    /* x in [9, 15] */
    else {

        /* P-1 */
        if (y < GRID_SIZE / 2 - 1) {
            return 2;
        }
        /* P-12 */
        else if (y == GRID_SIZE / 2 - 1) {
            return 7;
        }
        /* P-11 */
        else if (y == GRID_SIZE / 2) {
            return 8;
        }
        /* P-4 */
        else {
            return 3;
        }
    }
}

/* Read in an existing maze grid */
int readGrid(MazeCell maze[][]) {
  
  FILE * fp = fopen("maze.gd", "r");
  if (!fp) {
    return 0;
  }

  /* TODO Parse the file into the maze param */
}

/* Save maze grid to a file */
void writeGrid(MazeCell maze[][]) {
  FILE * fp = fopen("maze.gd", "r+");
  if (fp) {     
    /* Delete the file? */
  } 

  /* TODO Write the maze grid to the file */
}

/* Sets walls around the center 2x2 grid of the maze */
void setCenterWalls(MazeCell currCell) {
    MazeCell cell1 = maze[GRID_SIZE / 2][GRID_SIZE / 2];
    MazeCell cell2 = maze[GRID_SIZE / 2 + 1][GRID_SIZE / 2];
    MazeCell cell3 = maze[GRID_SIZE / 2][GRID_SIZE / 2 + 1];
    MazeCell cell4 = maze[GRID_SIZE / 2 + 1][GRID_SIZE / 2 + 1];

    if (currCell != cell1) {
        cell1.setNorth(true);
        cell1.setWest(true);
    }
    if (currCell != cell2) {
        cell2.setNorth(true);
        cell2.setEast(true);
    }
    if (currCell != cell3) {
        cell3.setSouth(true);
        cell3.setWest(true);
    }
    if (currCell != cell4) {
        cell4.setSouth(true);
        cell4.setEast(true);
    }
}

bool atGoal(MazeCell currCell) {
    if (goal == TO_START && currCell.getX() == 1 && currCell.getY() == GRID_SIZE) {
        return true;
    }
    if (goal == TO_CENTER &&
        (currCell.getX() == GRID_SIZE / 2 || currCell.getX() == GRID_SIZE / 2 + 1) &&
        (currCell.getY() == GRID_SIZE / 2 || currCell.getY() == GRID_SIZE / 2 + 1)) {
        return true;
    }
    return false;
}

/* For now, prioritize straight, N, E, S, W */
Direction getBestDirection(MazeCell currCell) {

    Direction bestDirection;
    int dist = currCell.getDist();
    
/*    if (dist > currCell.getNeighborDist(mouse.getDirection()) &&
        // check for wall) {
        bestDirection = 
        dist = 
    }*/

    /* Check north side */
    if (dist > currCell.getNeighborDistance(NORTH) &&
        !currCell.getNorth()) {
        bestDirection = NORTH;
        dist = currCell.getNeighborDistance(NORTH);
    }
    /* Check east side */
    if (dist > currCell.getNeighborDistance(EAST) &&
        !currCell.getEast()) {
        bestDirection = EAST;
        dist = currCell.getNeighborDistance(EAST);
    }
    /* Check south side */
    if (dist > currCell.getNeighborDistance(SOUTH) &&
        !currCell.getSouth()) {
        bestDirection = SOUTH;
        dist = currCell.getNeighborDistance(SOUTH);
    }
    /* Check west side */
    if (dist > currCell.getNeighborDistance(WEST) &&
        !currCell.getWest()) {
        bestDirection = WEST;
        dist = currCell.getNeighborDistance(WEST);
    }

    /* If there's a way, go that way. Otherwise, fix the maze */
    if (!bestDirection) {
        floodfill();
        return getBestDirection(currCell);
    } else {
        return bestDirection;
    }
}
