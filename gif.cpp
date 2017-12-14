#include "gif.h"
#include <fstream>

AnimatedGIF::AnimatedGIF(int width, int height, const char* filename, bool withAlpha, int delay)
    : Animation(width, height), count(0), delay(delay), offset_x(0), offset_y(0)
{
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        sprites.push_back(Sprite(line.c_str(), withAlpha));
    }
}

int AnimatedGIF::nextFrame(Canvas* canvas)
{
    RGBAMatrix image(width, height);
    image.addSprite(offset_x, offset_y, sprites[count]);
    image.writeToCanvas(canvas);
    count = (count + 1) % sprites.size();
    return delay;
}

PartyParrot::PartyParrot(int width, int height)
    : AnimatedGIF(width, height, "assets/parrot/parrot.lst", true, 40)
{
    offset_x = 20;
    offset_y = -30;
}

Flames::Flames(int width, int height)
    : AnimatedGIF(width, height, "assets/flames/flames.lst", false, 60)
{
    offset_y = -160;
}

SnowGif::SnowGif(int width, int height)
    : AnimatedGIF(width, height, "assets/snow/snow.lst", false, 130)
{

}

SlideShow::SlideShow(int width, int height)
    : AnimatedGIF(width, height, "assets/slideshow/slides.lst", false, 2000)
{

}
