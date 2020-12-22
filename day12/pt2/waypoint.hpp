#pragma once

class Waypoint {
public:
    Waypoint();
    int northSouth();
    int westEast();
    void rotateLeft(int degrees);
    void rotateRight(int degrees);
    void goNorth(int value);
    void goSouth(int value);
    void goEast(int value);
    void goWest(int value);

private:
    void doRotateLeft();
    void doRotateRight();

    int north;
    int south;
    int east;
    int west;
};
