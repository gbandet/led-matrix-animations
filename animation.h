#ifndef ANIMATION_H
#define ANIMATION_H

#include "canvas.h"
using namespace rgb_matrix;

class Animation
{
public:
    Animation(int width, int height);
    virtual int nextFrame(Canvas* canvas) = 0;

protected:
    int height;
    int width;
};

#endif // ANIMATION_H
