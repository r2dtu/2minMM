/*
 * File: Mouse.hpp
 * Author: David Tu
 * Last Updated: April 19, 2018
 * Description: Contains hardware compatible function prototypes and variables 
 * to physically move the mouse and read onboard sensors.
 */

#ifndef MOUSE_HPP
#define MOUSE_HPP

typedef enum {
    MOVE_FORWARD,
    MOVE_BACKWARD,
    ROTATE_LEFT,
    ROTATE_RIGHT
} MouseMovement;

class Mouse {
public:
    void moveMouse(MouseMovement mvt);
    void setWalls(MazeCell maze[][]);
    MazeCell getCurrCell();

private:
    MazeCell currCell;

    bool detectNorthWall(); 
    bool detectEastWall();
    bool detectSouthWall();
    bool detectWestWall();
    void readEncoders(int * channels);
    void readIR(int * irs);
    void readIMU(int * gyac);
};

#endif /* MOUSE_HPP */
