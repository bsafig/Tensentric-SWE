#pragma once

#include <vector>
#include <deque>
#include "ParkingSpot.h"
using namespace std;

class Grid {
    vector<ParkingSpot> spots;
    vector<Puck> pucks;
    deque<Puck*> queue;

    void init();

public:
    /**
     * @brief Construct a new Grid object
     */
    Grid();

    /**
     * @brief Prints current states of all parking spots
     */
    void printState();
    
    /**
     * @brief Generates pucks and places them randomly on the grid
     * 
     * @param numPucks number of pucks to generate
     */
    void generatePucks(int numPucks);

    /**
     * @brief Assigns each puck to the closest available parking spot
     */
    void assignClosestSpots();

    /**
     * @brief Closes gaps between empty parking spots and occupied ones
     */
    void closeGaps();
    
    /**
     * @brief Fills the queue with pucks that need to work
     */
    void createWorkQueue();

    /**
     * @brief Process and cycles through the current work queue
     */
    void processWorkQueue();
    
    /**
     * @brief Shifts all pucks forward one spot in the grid
     */
    void shiftPucksForward();
    
    // Testing methods for gtest
    void setPucks(const vector<Puck>& newPucks) { pucks = newPucks; }
    vector<ParkingSpot> getSpots() const { return spots; }
};