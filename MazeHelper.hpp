/*
 * File: MazeHelper.hpp
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: Maze representation helper variables and functions.
 */

#ifndef MAZE_HELPER_HPP
#define MAZE_HELPER_HPP

#define GRID_SIZE 16

/* Partition-central algorithm:
 * This enum is used to determine which wall-following / direction
 * strategy the mouse should follow.
 *
 * Left-hand: precedence to left, then straight, then right.
 * Right-hand: precedence to right, then straight, then left.
 * Central-left: precedence to straight, then left, then right.
 * Central-right: precedence to straight, then right, then left.
 * Central-trend: take precedence to the endpoint, located in the
 *                4-unit square area on the maze center.
 */
typedef enum {
  LH,
  RH,
  CL,
  CR,
  CT
} PartitionRule;

/* Absolute compass direction with respect to initial starting position of
 * mouse being NORTH. */
typedef enum {
    NORTH,
    EAST,
    SOUTH,
    WEST
} Direction;

/* Functions */
void initGrid(MazeCell maze[][]);
int readGrid(MazeCell maze[][]);
void writeGrid(MazeCell maze[][]);

void setWalls(MazeCell cell);
PartitionRule nextCellStrategy(int partition, Direction dir);
int getMinNeighborDist(MazeCell cell);
int MFF();

int getPartition(int x, int y, int size);
PartitionRule nextCellStrategy(int partition, Direction dir);

#endif /* MAZE_HELPER_HPP */
