#define PARKINGSPOT_H

#include "Puck.h"

struct ParkingSpot {
    int xPos, yPos;
    Puck* puck = nullptr;

    bool isEmpty() const {
        return !puck;
    }
};