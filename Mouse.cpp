/*
 * File: main.c
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: An OO representation of the MM: implements Mouse methods.
 */
#include "Mouse.hpp"

MazeCell Mouse::getCurrCell() {
    return currCell;
}

void Mouse::move(MouseMovement mvt) {

  /* TODO Only need to worry about partitions when more than one neighbor cell 
   * has same distance value */
  
}

/* Check for surrounding walls and update the mazeCells grid. */
void setWalls() {

  /* If a wall detected from any sensor, record it */
  if (detectNorthWall()) {
    getCurrCell().setNorth(true);
  }
  if (detectEastWall()) {
    getCurrCell().setEast(true);
  }
  if (detectSouthWall()) {
    getCurrCell().setSouth(true);
  }
  if (detectWestWall()) {
    getCurrCell().setWest(true);
  }
}

bool Mouse::detectNorthWall() {
  /* TODO Turn on side, front facing sensors */
}

bool Mouse::detectEastWall() {
  /* TODO (1 or 2)
   * 1) Turn on side, diagonal facing sensors
   * 2) Turn 90 deg right, turn on side, front facing sensors
   */
}

bool Mouse::detectSouthWall() {
  /* Is there really a need for this? */
}

bool Mouse::detectWestWall() {
  /* TODO (1 or 2)
   * 1) Turn on side, diagonal facing sensors
   * 2) Turn 90 deg left, turn on side, front facing sensors
   */
}

void Mouse::readEncoders(int * channels) {

}

/* IRs serves as input and output parameter */
void Mouse::readIR(int * irs) {

}

void Mouse::readIMU(int * gyac) {

}

