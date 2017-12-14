#ifndef LASER_H
#define LASER_H

#include <list>
#include "animation.h"

using namespace std;

struct LaserLine {
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int current;
    int length;
    int color;
};

class Laser : public Animation
{
public:
    Laser(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;

private:
    list<LaserLine> lines;
};

#endif // LASER_H
