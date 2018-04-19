/*
 * File: MazeCell.hpp
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: Contains the definition and information needed for each cell.
 */

#ifndef MAZE_CELL_HPP
#define MAZE_CELL_HPP

/* 16x16 maze, ea 18cm x 18cm 
 * Each square will be represented by 6 values: 4 for walls, 1 for
 * visited, and 1 for distance from center of maze (updated with MFF).
 */
class MazeCell {
public:
    char getX();
    char getY();
    char getPartition();
    bool hasNorth();
    bool hasEast();
    bool hasSouth();
    bool hasWest();
    bool hasVisited();
    short getDist();
    
    void setX(char x);
    void setY(char y);
    void setPartition(char part);
    void setNorth(bool n);
    void setEast(bool e);
    void setSouth(bool s);
    void setWest(bool w);
    void setVisited(bool visited);
    void setDist(short dist);
    
    short getNeighborDistance(Direction dir);

private:
    char x, y, part;
    bool n, e, s, w;
    bool visited;
    short dist;
};

#endif /* MAZE_CELL_HPP */
