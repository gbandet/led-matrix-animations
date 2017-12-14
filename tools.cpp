#include "tools.h"

Color Tools::hsv_to_rgb(float h, float s, float v)
{
    if (h < 0 || h > 360 || s < 0 || s > 1 || v < 0 || v > 1) {
        return Color(0, 0, 0);
    }
    //if (h == 360)
    float hh = h / 60.;
    int hi = (int) hh;
    float hr = hh - hi;

    float p = v * (1. - s);
    float q = v * (1. - (s * hr));
    float t = v * (1. - (s * (1. - hi)));

    float r, g, b;

    switch (hi) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;
    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
    default:
        r = v;
        g = p;
        b = q;
        break;
    }
    return Color(
        (int) (r >= 1 ? 255 : r * 256),
        (int) (g >= 1 ? 255 : g * 256),
        (int) (b >= 1 ? 255 : b * 256));
}
