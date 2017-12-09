#ifndef FREQHISTOGRAM_H
#define FREQHISTOGRAM_H

#include "animation.h"
#include "canvas.h"

class FreqHistogram : public Animation
{
public:
    FreqHistogram(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;
};

#endif // FREQHISTOGRAM_H
