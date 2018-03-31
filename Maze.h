/*
 * File: Maze.h
 * Author: Clark Phan & David Tu
 * Last Updated: February 3, 2018
 * Description: 
 */

#ifndef MAZE_H
#define MAZE_H

#define GRID_SIZE 12

/* 16x16 maze, ea 18cm x 18cm 
 * Each square will be represented by 6 values: 4 for walls, 1 for
 * visited, and 1 for distance from center of maze (updated with MFF).
 */
struct maze_cell {
  char n;
  char e;
  char s;
  char w;
  bool visited;
  short dist;
};

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

#endif /* MAZE_H */
