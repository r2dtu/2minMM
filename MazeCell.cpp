/*
 * File: MazeCell.cpp
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: Implementation of maze cell information storage.
 */

#include "MazeCell.hpp"

char MazeCell::getX() {
    return x;
}

char MazeCell::getY() {
    return y;
}

char MazeCell::getPartition() {
    return part;
}

bool MazeCell::getNorth() {
    return n;
}

bool MazeCell::getEast() {
    return e;
}

bool MazeCell::getSouth() {
    return s;
}

bool MazeCell::getWest() {
    return w;
}

bool MazeCell::hasVisited() {
    return visited;
}

short MazeCell::getDist() {
    return dist;
}

void MazeCell::setX(char x) {
    this->x = x;
}

void MazeCell::setY(char y) {
    this->y = y;
}

void MazeCell::getPartition(char part) {
    this->part = part;
}

void MazeCell::setNorth(bool n) {
    this->n = n;
}

void MazeCell::setEast(bool e) {
    this->e = e;
}

void MazeCell::setSouth(bool s) {
    this->s = s;
}

void MazeCell::setWest(bool w) {
    this->w = w;
}

void MazeCell::setVisited(bool visited) {
    this->visited = visited;
}

void MazeCell::setDist(short dist) {
    this->dist = dist;
}

short MazeCell::getNeighborDistance(MazeCell maze[][], Direction dir) {
    MazeCell neighbor;
    if (dir == NORTH && getY() != 1) {
        neighbor = maze[getX()][getY() - 1];
    } else if (dir == EAST && getX() != GRID_SIZE) {
        neighbor = maze[getX() + 1][getY()];
    } else if (dir == SOUTH && getY() != GRID_SIZE) {
        neighbor = maze[getX()][getY() + 1];
    } else if (dir == WEST && getX() != 1) {
        neighbor = maze[getX() - 1][getY()];
    } else {
        return DEAD;
    }
    return neighbor.getDist();
}

