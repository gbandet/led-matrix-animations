#ifndef TOOLS_H
#define TOOLS_H

#include "graphics.h"

using namespace rgb_matrix;

class Tools
{
public:
    static Color hsv_to_rgb(float h, float s, float v);

private:
    Tools() {}
};

#endif // TOOLS_H
