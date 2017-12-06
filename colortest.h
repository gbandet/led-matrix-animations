#ifndef COLORTEST_H
#define COLORTEST_H

#include "animation.h"

class ColorTest : public Animation
{
public:
    ColorTest(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;

private:
    int count;
};

#endif // COLORTEST_H
