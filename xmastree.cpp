#include "xmastree.h"

XMasTree::XMasTree(int width, int height)
    : Animation(width, height), sprite("assets/xmastree.png")
{}


int XMasTree::nextFrame(Canvas* canvas)
{
    RGBAMatrix image(width, height);
    image.addSprite(0, 0, sprite);
    image.writeToCanvas(canvas);
    return 500;
}
