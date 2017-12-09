#include "circles.h"
#include "screen.h"
#include <vector>

using namespace std;

const int RING_COUNT = 7;
const int RING_WIDTH = 4;

vector<Pixel> colors = {Pixel(255, 0, 0, 1), Pixel(0, 255, 0, 1), Pixel(255, 255, 0, 1), Pixel(0, 0, 255, 1)};

Circles::Circles(int width, int height)
    : Animation(width, height), count(0)
{}

int Circles::nextFrame(Canvas* canvas)
{
    RGBAMatrix image(width, height);
    int centerx = width / 2;
    int centery = height / 2;
    int color = (count / RING_WIDTH) % colors.size();
    int radius = count % RING_WIDTH;
    image.drawRing(centerx, centery, 0, radius, colors[color]);
    for (int i = 0; i < RING_COUNT; i++) {
        color = (color - 1) % colors.size();
        image.drawRing(centerx, centery, radius + 1, radius + RING_WIDTH, colors[color]);
        radius += RING_WIDTH;
    }
    color = (color - 1) % colors.size();
    if (count % RING_WIDTH != RING_WIDTH - 1) {
        image.drawRing(centerx, centery, radius + 1, RING_COUNT * RING_WIDTH - 1, colors[color]);
    }

    image.writeToCanvas(canvas);
    count++;
    return 100;
}
