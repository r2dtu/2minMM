/*
 * File: main.c
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: Main code running on the MM.
 */
#include <queue>
#include <stack>

#include "mbed.h"
#include "Mouse.hpp"
#include "MazeCell.hpp"
#include "MazeHelper.hpp"

int main() {

    MazeCell mazeCells[GRID_SIZE][GRID_SIZE];
    
    // Read grid from file
    int result = readGrid(mazeCells);

    // If no file exists, initialize the grid
    if (!result) {

        // Initialize cells for modified floodfill algorithm
        initGrid(mazeCells);
    }
    
    /* Go in and out. */
    doMaze(mazeCells);

    /* Write maze grid to file to remember for next iteration */
    writeGrid(mazeCells);
}

/* Do the maze lol */
void doMaze(MazeCell maze[][]) {

    // Initialize a mouse
    Mouse mouse(0, 0);
    std::queue<MouseMovement> moveQueue;

    // Find the center
    while (!mouse.atCenter()) {
        MouseMovement nextStep = nextStep(mouse, moveQueue);
        mouse.move(nextStep);
    }

    // Go back to the start
    while (!mouse.atStart()) {
        MouseMovement nextStep = nextStep(mouse, moveQueue);
        mouse.move();
    }
}

/* Determines which way the micromouse should turn or move next. */
MouseMovement nextStep(Mouse mouse, std::queue<MouseMovement> moveQueue) {

    MouseMovement next;
    MazeCell currCell = mouse.getCurrCell();

    // We need to figure out which way to move next
    if (moveQueue.empty()) {

        // New cell? Explore it.
        if (!currCell.hasVisited()) {
            mouse.checkForWalls(currCell);
            currCell.setVisited(true);
        }

        // Are we at the goal yet?
        if (currCell.isGoal()) {
            setCenterWalls(currCell);
            goal = !goal; // TODO
            floodfill();
        }
        
        // Get the next best direction
        nextDirection = getBestDirection(currCell);
        //turbo = getNeighborExplored(nextDirection);
        
        // Figure out which way the robot should turn
        if (nextDirection == currentDirection) {
            next = MOVE_FORWARD;
        } else if () {
            next = ROTATE_LEFT;
            moveQueue.add(MOVE_FORWARD);
        } else if () {
            next = ROTATE_RIGHT;
            moveQueue.add(MOVE_FORWARD);
        } else {
            next = MOVE_BACKWARD;
        }
    } else {
        next = moveQueue.top();
        moveQueue.pop();
    }

    return next;
}

/*
 * Perform floodfill on maze.
 *
 * 1) Push current cell location onto stack.
 * 2) While stack is not empty:
 *      Pop cell location from the stack.
 *      If the minimum distance of neighboring OPEN cells md ≠ currCell
 *      distance - 1, replace currCell distance with md + 1, and push ALL
 *      neighboring locations onto stack (except the centers).??
 */
void floodfill(MazeCell currCell) {
    std::stack<MazeCell> ffStack;

    /* BACK OUT */
    ffStack.push(currCell);

//    if (goal == TO_START) {
//        MazeCell start = maze[0][0];
//        start.setDistance(0);
//        ffStack.add(start);
//        speedy = false;
//    } else {
//        MazeCell center1 = maze[GRID_SIZE / 2][GRID_SIZE / 2];
//        MazeCell center2 = maze[GRID_SIZE / 2 + 1][GRID_SIZE / 2];
//        MazeCell center3 = maze[GRID_SIZE / 2][GRID_SIZE / 2 + 1];
//        MazeCell center4 = maze[GRID_SIZE / 2 + 1][GRID_SIZE / 2 + 1];
//        center1.setDistance(0);
//        center2.setDistance(0);
//        center3.setDistance(0);
//        center4.setDistance(0);
//        if (speedRun && speedRunCapable) {
//            speedy = true;
//        } else {
//            speedy = false;
//        }
//    }
    /* GOING IN */
    while (!ffStack.empty()) {
        MazeCell cell = ffStack.top();
        ffStack.pop();
        short dist = cell.getDist();

        // Does north have wall?
        if (!currCell.getNorth()) {
            MazeCell northCell = mazeCells[cell.getX()][cell.getY() - 1];
            if ((dist + 1 < getNeighborDistance(mazeCells, NORTH)) &&
                (speedy == false || northCell.hasVisited())) {
                ffStack.push(northCell);
                northCell.setDistance(dist + 1);
            }
        }
        // Does east have wall?
        if (!currCell.getEast()) {
            MazeCell eastCell = mazeCells[cell.getX() + 1][cell.getY()];
            if ((dist + 1 < getNeighborDistance(mazeCells, EAST)) &&
                (speedy == false || eastCell.hasVisited())) {
                ffStack.push(eastCell);
                eastCell.setDistance(dist + 1);
            }
        }
        // Does south have wall?
        if (!currCell.getSouth()) {
            MazeCell southCell = mazeCells[cell.getX()][cell.getY() + 1];
            if ((dist + 1 < getNeighborDistance(mazeCells, SOUTH)) &&
                (speedy == false || southCell.hasVisited())) {
                ffStack.push(southCell);
                southCell.setDistance(dist + 1);
            }
        }
        // Does west have wall?
        if (!currCell.getWest()) {
            MazeCell westCell = mazeCells[cell.getX() - 1][cell.getY()];
            if ((dist + 1 < getNeighborDistance(mazeCells, WEST)) &&
                (speedy == false || westCell.hasVisited())) {
                ffStack.push(westCell);
                westCell.setDistance(dist + 1);
            }
        }
    }
    
    if (currCell.getDist() == USELESS) {
        // Reset maze
        // checkForWalls(currCell);
        // floodfill();
    }
}

