#pragma once

/**
 * @brief Represents a puck that can be assigned to parking spots
 */
class Puck {
    int id, xPose, yPose;

    public:
    /**
     * @brief Construct a new Puck object
     * 
     * @param id identifier for the puck
     * @param x x position
     * @param y y position
     */
    Puck(int id, int x, int y);

    /**
     * @brief Simulates work done by the puck
     */
    void Work();

    /**
     * @brief Moves the given puck to the specified coordinates
     * 
     * @param x target x position
     * @param y target y position
     */
    void MoveTo(int x, int y);

    int getId() const;
    int getX() const;
    int getY() const;
};