#include "maze.h"

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



