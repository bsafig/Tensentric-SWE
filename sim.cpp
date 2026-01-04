#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Grid.h"
using namespace std;

int main() {
    Grid grid;

    // Seed random number generator
    srand(static_cast<unsigned int>(time(0)));

    // Initial setup
    grid.generatePucks(rand() % 9 + 1);
    grid.assignClosestSpots();
    cout << "Initial Path:" << endl;
    grid.printState();

    // Close gaps
    grid.closeGaps();
    cout << "Aggregated Path" << endl;
    grid.printState();

    // Process work queue
    grid.createWorkQueue();
    grid.processWorkQueue();

    return 0;
};