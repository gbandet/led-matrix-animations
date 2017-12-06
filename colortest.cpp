#include "colortest.h"

ColorTest::ColorTest(int width, int height)
    : Animation(width, height), count(0)
{
}

int ColorTest::nextFrame(Canvas* canvas)
{
    count += 1;
    count = count % 4;
    switch (count) {
    case 1:
        canvas->Fill(255, 0, 0);
        break;
    case 2:
        canvas->Fill(0, 255, 0);
        break;
    case 3:
        canvas->Fill(0, 0, 255);
        break;
    default:
        canvas->Fill(0, 0, 0);
    }
    return 1500;
}
