#include "Grid.h"

#include <iostream>
#include <cmath>
#include <thread>
#include <string>

using namespace std;

Grid::Grid() {
    init();
}

void Grid::init() {
    int xs[] = {180, 300, 420};
    int ys[] = {60, 180, 300};

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 3; x++) {
            spots.push_back({xs[x], ys[y], nullptr});
        }
    }
}

void Grid::printState() {
    string msg = "START -> ";

    for (size_t i = 0; i < spots.size(); i++) {
        if (!spots[i].isEmpty()) {
            msg += "Puck " + to_string(spots[i].puck->getId());
        } else {
            msg += "EMPTY";
        }
        msg += " -> ";
    }

    msg += "END\n";
    cout << msg << endl;
}

void Grid::generatePucks(int numPucks) {
    cout << "Initial Positions:" << endl;

    for (int i = 0; i < numPucks; i++) {
        pucks.emplace_back(
            i,
            rand() % 480,
            rand() % 480
        );

        cout << "Puck " << i << " at ("
             << pucks.back().getX() << ", "
             << pucks.back().getY() << ")"
             << endl;
    }
    cout << endl;
}

void Grid::assignClosestSpots() {
    cout << "Assigning Pucks to Closest Spots:" << endl;

    for (Puck& p : pucks) {
        double closest = -1.0;
        int spotIndex = -1;

        for (size_t i = 0; i < spots.size(); i++) {
            if (!spots[i].isEmpty()) continue;

            double dist = hypot(
                p.getX() - spots[i].xPos,
                p.getY() - spots[i].yPos
            );

            if (closest == -1 || dist < closest) {
                closest = dist;
                spotIndex = i;
            }
        }

        spots[spotIndex].puck = &p;
        p.MoveTo(spots[spotIndex].xPos, spots[spotIndex].yPos);
    }

    cout << "Assignment complete\n" << endl;
}

void Grid::closeGaps() {
    cout << "Closing Gaps Between Pucks:\n";

    for (int i = spots.size() - 1; i >= 0; i--) {
        if (spots[i].isEmpty()) {
            for (int j = i - 1; j >= 0; j--) {
                if (!spots[j].isEmpty()) {
                    spots[i].puck = spots[j].puck;
                    spots[j].puck->MoveTo(
                        spots[i].xPos,
                        spots[i].yPos
                    );
                    spots[j].puck = nullptr;
                    break;
                }
            }
        }
    }

    cout << "Gaps closed.\n\n";
}

void Grid::createWorkQueue() {
    queue.clear();
    for (auto& spot : spots) {
        if (!spot.isEmpty()) {
            queue.push_back(spot.puck);
        }
    }
}

void Grid::processWorkQueue() {
    cout << "=== START WORK ===\n" << endl;

    while (!queue.empty()) {
        Puck* active = queue.back();
        queue.pop_back();

        cout << "Performing work on puck number "
             << active->getId() << ".\n";

        thread worker([active]() {
            active->Work();
        });

        shiftPucksForward();
        printState();

        worker.join();
        cout << "Work completed.\n\n";

        spots[0].puck = active;
        closeGaps();
    }

    cout << "=== END WORK ===\n" << endl;
}

void Grid::shiftPucksForward() {
    int size = spots.size() - 1;

    for (int i = size; i > 0; i--) {
        spots[i].puck = spots[i - 1].puck;
        if (spots[i].puck) {
            spots[i].puck->MoveTo(
                spots[i].xPos,
                spots[i].yPos
            );
        }
    }

    spots[0].puck = nullptr;
}