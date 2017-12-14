#include "gif.h"
#include <fstream>
#include "graphics.h"

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

XmasParrot::XmasParrot(int width, int height)
    : AnimatedGIF(width, height, "assets/xmas-parrot/xmas-parrot.lst", true, 40)
{
    offset_x = 20;
    offset_y = -27;
}

JediParrot::JediParrot(int width, int height)
    : AnimatedGIF(width, height, "assets/jediparrot/jediparrot.lst", true, 40)
{
    offset_x = 20;
    offset_y = -27;
}

SithParrot::SithParrot(int width, int height)
    : AnimatedGIF(width, height, "assets/sith-parrot/sith-parrot.lst", true, 40)
{
    offset_x = 20;
    offset_y = -27;
}

SaberParrot::SaberParrot(int width, int height)
    : AnimatedGIF(width, height, "assets/saber-parrot/saber-parrot.lst", true, 40)
{}


Flames::Flames(int width, int height)
    : AnimatedGIF(width, height, "assets/flames/flames.lst", false, 60)
{
    offset_y = -160;
}

SnowGif::SnowGif(int width, int height)
    : AnimatedGIF(width, height, "assets/snow/snow.lst", false, 130)
{}

WinterSnowGif::WinterSnowGif(int width, int height)
    : AnimatedGIF(width, height, "assets/snow/snow.lst", false, 130)
{
    font.LoadFont("assets/fonts/10x20.bdf");
}

int WinterSnowGif::nextFrame(Canvas* canvas)
{
    int delay = AnimatedGIF::nextFrame(canvas);
    DrawText(canvas, font, 25, 58, Color(255, 0, 0), 0, "Winter 2017");
    return delay;
}

SlideShow::SlideShow(int width, int height)
    : AnimatedGIF(width, height, "assets/slideshow/slides.lst", false, 500), wait_count(0)
{}

int SlideShow::nextFrame(Canvas *canvas) {
    wait_count++;
    int delay = AnimatedGIF::nextFrame(canvas);
    if (wait_count % 10 != 0) {
        count = (count - 1) % sprites.size();
    }
    return delay;
}
