#include "gif.h"

AnimatedGIF::AnimatedGIF(int width, int height, const char* filename, int delay)
    : Animation(width, height), count(0), delay(delay), offset_x(0), offset_y(0)
{
    CImgList<unsigned char> gif;
    gif.load_gif_external(filename);
    for (int i = 0; i < gif.width(); i++) {
        sprites.push_back(Sprite(gif.at(i)));
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
    : AnimatedGIF(width, height, "assets/parrot.gif", 40)
{
    offset_x = 20;
    offset_y = -30;
}

Flames::Flames(int width, int height)
    : AnimatedGIF(width, height, "assets/flames.gif", 60)
{
    sprites.erase(sprites.begin());
    offset_y = -175;
}
