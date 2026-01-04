#include "Puck.h"
#include <iostream>
#include <thread>
using namespace std;

Puck::Puck(int id, int x, int y) {
    this->id = id;
    this->xPose = x;
    this->yPose = y;
}

void Puck::Work() {
    this_thread::sleep_for(500ms);
}

void Puck::MoveTo(int x, int y) {
    cout << "Moving puck " << id << " to position (" << x << ", " << y << ").\n";
    xPose = x;
    yPose = y;
}

int Puck::getId() const { return id; }
int Puck::getX() const { return xPose; }
int Puck::getY() const { return yPose; }