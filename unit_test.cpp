#include "gtest/gtest.h"
#include "Grid.h"
#include "Puck.h"
#include "ParkingSpot.h"
#include <vector>
#include <iostream>
using namespace std;

TEST(GridTests, ShiftSinglePuck) {
    Grid grid;

    vector<Puck> testPucks = {
        Puck(0, 180, 180)
    };
    grid.setPucks(testPucks);
    grid.assignClosestSpots();
    grid.shiftPucksForward();
    vector<ParkingSpot> resultSpots = grid.getSpots();

    EXPECT_FALSE(resultSpots[4].isEmpty()) << "Expected spot 4 to be occupied.";
}