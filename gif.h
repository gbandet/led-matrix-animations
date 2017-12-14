#ifndef GIF_H
#define GIF_H

#include <vector>
#include <string>
#include "animation.h"
#include "screen.h"

using namespace std;

class AnimatedGIF : public Animation
{
public:
    AnimatedGIF(int width, int height, const char* filename, bool withAlpha = true, int delay=100);
    virtual int nextFrame(Canvas* canvas) override;
protected:
    vector<Sprite> sprites;
    int count;
    int delay;
    int offset_x;
    int offset_y;
};

class PartyParrot : public AnimatedGIF
{
public:
    PartyParrot(int width, int height);
};

class Flames : public AnimatedGIF
{
public:
    Flames(int width, int height);
};

class SnowGif : public AnimatedGIF
{
public:
    SnowGif(int width, int height);
};

class SlideShow : public AnimatedGIF
{
public:
    SlideShow(int width, int height);
};

#endif // GIF_H
