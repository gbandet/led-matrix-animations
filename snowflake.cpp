#include "snowflake.h"
#include <functional>
#include <stdlib.h>
#include <vector>
#include "screen.h"

const int MAX_SNOWFLAKES = 10;

SnowflakeAnimation::SnowflakeAnimation(int width, int height)
    : Animation(width, height), sprite("assets/snowflake.png")
{}

int SnowflakeAnimation::nextFrame(Canvas* canvas)
{
    for (list<SnowFlake>::iterator it = snowflakes.begin(); it != snowflakes.end(); ++it) {
        it->y += it->speed;
        if (it->y >= height) {
            it = snowflakes.erase(it);
        }
    }

    if (rand() % 5 > 3 && snowflakes.size() < MAX_SNOWFLAKES) {
        SnowFlake snowflake;
        snowflake.x = rand() % width;
        snowflake.y = 1 - sprite.height;
        snowflake.speed = 2 + rand() % 3;
        snowflakes.push_back(snowflake);
    }

    RGBAMatrix image(width, height);
    for (list<SnowFlake>::iterator it = snowflakes.begin(); it != snowflakes.end(); ++it) {
        image.addSprite(it->x, it->y, sprite);
    }
    image.writeToCanvas(canvas);

    return 100;
}
