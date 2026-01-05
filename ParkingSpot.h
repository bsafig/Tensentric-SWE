#pragma once

#include "Puck.h"

/**
 * @brief Represents a parking spot on the grid
 */
struct ParkingSpot {
    int xPos, yPos;
    Puck* puck = nullptr;

    bool isEmpty() const {
        return !puck;
    }
};