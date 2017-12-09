#include "freqhistogram.h"
#include "screen.h"
#include <random>

const int BAR_COUNT = 10;
const int BAR_SPACING = 4;
const int VERTICAL_MARGIN = 5;

FreqHistogram::FreqHistogram(int width, int height)
    : Animation(width, height)
{}

int FreqHistogram::nextFrame(Canvas* canvas)
{
    int bar_width = width / BAR_COUNT - BAR_SPACING;
    int max_height = height - 2 * VERTICAL_MARGIN;

    RGBAMatrix image(width, height);
    for (int i = 0; i < BAR_COUNT; i++) {
        int value = rand() % max_height;
        for (int dx = 0; dx < bar_width; dx++) {
            int x = BAR_SPACING / 2 + (bar_width + BAR_SPACING) * i + dx;
            for (int y = 0; y < value; y++) {
                float percent =  y / (float) max_height;
                Pixel color;
                if (percent < .4) {
                    color = Pixel(0, 255, 0, 1);
                } else if (percent < .6) {
                    color = Pixel(128, 255, 0, 1);
                } else if (percent < .8) {
                    color = Pixel(255, 255, 0, 1);
                } else {
                    color = Pixel(255, 0, 0, 1);
                }
                image.setPixel(x, height - VERTICAL_MARGIN - y, color);
            }
        }
    }

    image.writeToCanvas(canvas);
    return 200;
}
