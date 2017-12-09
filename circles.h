#ifndef CIRCLES_H
#define CIRCLES_H

#include "animation.h"

class Circles : public Animation
{
public:
    Circles(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;

private:
    int count;
};

#endif // CIRCLES_H
