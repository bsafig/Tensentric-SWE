#ifndef GRID_H
#define GRID_H

#include <vector>
#include <deque>
#include "ParkingSpot.h"
using namespace std;

class Grid {
    vector<ParkingSpot> spots;
    vector<Puck> pucks;
    deque<Puck*> queue;

public:
    Grid();

    void init();
    void printState();

    void generatePucks(int numPucks);
    void assignClosestSpots();
    void closeGaps();

    void createWorkQueue();
    void processWorkQueue();

    void shiftPucksForward();
};
#endif