#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include <cmath>
#include <deque>
using namespace std;

class Puck {
    int id, xPose, yPose;

    public:

    Puck(int id, int x, int y) {
        this->id = id;
        this->xPose = x;
        this->yPose = y;
    }

    void Work() {
        cout << "Performing work on puck number " << id << ".\n";
        this_thread::sleep_for(100ms);
        cout << "Work on puck " << id << " completed.\n";
    }

    void MoveTo(int x, int y) {
        cout << "Moving puck " << id << " to position (" << x << ", " << y << ").\n";
        xPose = x;
        yPose = y;
    }

    int getId() const { return id; }
    int getX() const { return xPose; }
    int getY() const { return yPose; }
};

struct ParkingSpot {
    int xPos, yPos;
    Puck* puck = nullptr;

    bool isEmpty() const {
        return !puck;
    }
};

class Grid {
    vector<ParkingSpot> spots;
    vector<Puck> pucks;
    deque<Puck*> queue;

    public:

    Grid() {
        init();
    }

    void init() {
        int xs[] = {180, 300, 420};
        int ys[] = {60, 180, 300};

        for (int y = 0; y < 3; y++) {
            for (int x = 0; x < 3; x++) {
                spots.push_back({xs[x], ys[y], nullptr});
            }
        }
    }

    void printState() {
        string msg = "START -> ";

        for (size_t i = 0; i < spots.size(); i++) {
            if(!spots[i].isEmpty()) {
                msg += "Puck " + to_string(spots[i].puck->getId());
            } else {
                msg += "EMPTY";
            }

            msg += " -> ";
        }
        msg += "END\n";
        cout << msg << endl;
    }

    void generatePucks(int numPucks) {
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
    };

    void assignClosestSpots() {
        cout << "Assigning Pucks to Closest Spots:" << endl;

        // Loop by address to access original pucks
        for (Puck &p : pucks) {
            double closest = -1.0;
            int spotIndex = -1;
            for(long unsigned int x = 0; x < spots.size(); x++) {
                if(!spots[x].isEmpty()) continue;

                double dist = hypot(
                    p.getX() - spots[x].xPos,
                    p.getY() - spots[x].yPos
                );
                if (closest == -1 || dist < closest) {
                    closest = dist;
                    spotIndex = x;
                }
            }
            spots[spotIndex].puck = &p;
            p.MoveTo(spots[spotIndex].xPos, spots[spotIndex].yPos);
        }
        cout << "Assignment complete\n" << endl;
    }

    void closeGaps() {
        cout << "Closing Gaps Between Pucks:\n";

        queue.clear();

        // Collect pucks in spot order (tail → head)
        for (auto& spot : spots) {
            if (!spot.isEmpty()) {
                queue.push_back(spot.puck);
                spot.puck = nullptr;
            }
        }

        // Reassign from the BACK
        int start = spots.size() - queue.size();
        for (size_t i = 0; i < queue.size(); i++) {
            spots[start + i].puck = queue[i];
            queue[i]->MoveTo(
                spots[start + i].xPos,
                spots[start + i].yPos
            );
        }

        cout << "Gaps closed.\n\n";
    }

    void processWorkQueue() {
        cout << "=== START WORK ===\n" << endl;

        while (!queue.empty()) {
            Puck* active = queue.back();
            queue.pop_back();

            // TODO: Use a thread to simulate asynchronous work
            active->Work();

            shiftPucksForward();
            printState();
        }

        cout << "=== END WORK ===\n" << endl;
    }


    void shiftPucksForward() {
        int size = spots.size() - 1;
        Puck* tmp = spots[size].puck;

        for (size_t i = size; i > 0; i--) {
            spots[i].puck = spots[i - 1].puck;
            if (spots[i].puck) {
                spots[i].puck->MoveTo(
                    spots[i].xPos,
                    spots[i].yPos
                );
            }
        }
        spots[0].puck = tmp;
    }

};

int main() {
    Grid grid;

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
    grid.processWorkQueue();

    return 0;
};