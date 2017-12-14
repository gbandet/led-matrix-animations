#include "laser.h"
#include "screen.h"
#include <stdlib.h>
#include <math.h>
#include "graphics.h"
#include "tools.h"

const int LINE_COUNT =  16;
const vector<Color> COLORS = {
    Color(255, 0, 0),
    Color(0, 255, 0),
    Color(0, 255, 255),
    Color(255, 255, 255),
};

Laser::Laser(int width, int height)
    : Animation(width, height)
{}

int Laser::nextFrame(Canvas *canvas)
{
    int centerx = width / 2;
    int centery = height / 2;

    for (list<LaserLine>:: iterator it = lines.begin(); it != lines.end(); ++it) {
        it->current++;
        if (it->current > it->length) {
            it = lines.erase(it);
        }
    }

    for (int i = 0; i < LINE_COUNT - lines.size(); i++) {
        LaserLine line;
        line.start_x = (rand() % (width + 20)) - 10;
        line.start_y = (rand() % (height + 20)) - 10;
        line.end_x = (rand() % (width + 20)) - 10;
        line.end_y = (rand() % (height + 20)) - 10;
        line.current = 0;
        line.length = (rand() % 20) + 10;
        line.color = rand() % COLORS.size();
        lines.push_back(line);
    }

    canvas->Fill(0, 0, 0);
    for (list<LaserLine>:: iterator it = lines.begin(); it != lines.end(); ++it) {
        float ratio = it->current / (float) it->length;
        float currentx = (it->end_x - it->start_x) * ratio + it->start_x;
        float currenty = (it->end_y - it->start_y) * ratio + it->start_y;
        rgb_matrix::DrawLine(canvas, centerx, centery, round(currentx), round(currenty), COLORS[it->color]);
        //rgb_matrix::DrawLine(canvas, centerx, centery, round(currentx), round(currenty), Tools::hsv_to_rgb(120., 1., 1.));
    }

    return 50;
}
