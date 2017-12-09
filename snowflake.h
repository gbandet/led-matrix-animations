#ifndef SNOWFLAKE_H
#define SNOWFLAKE_H

#include <list>
#include "animation.h"
#include "screen.h"

using namespace std;

struct SnowFlake {
    int x;
    int y;
    int speed;
};



class SnowflakeAnimation : public Animation
{
public:
    SnowflakeAnimation(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;

private:
    list<SnowFlake> snowflakes;
    Sprite sprite;
    int counter;
};

#endif // SNOWFLAKE_H
