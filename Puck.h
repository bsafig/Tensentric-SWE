#ifndef PUCK_H
#define PUCK_H

class Puck {
    int id, xPose, yPose;

    public:
    Puck(int id, int x, int y);

    void Work();
    void MoveTo(int x, int y);

    int getId() const;
    int getX() const;
    int getY() const;
};
#endif