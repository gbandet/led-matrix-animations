#ifndef SCREEN_H
#define SCREEN_H

#include <vector>
#include <stdlib.h>
#include <functional>

#define cimg_use_png
#include "CImg.h"

#include "canvas.h"

using namespace rgb_matrix;
using namespace cimg_library;
using namespace std;

class Pixel {
public:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
    float alpha;

    Pixel() : red(0), green(0), blue(0), alpha(1.) {}
    Pixel(uint8_t red, uint8_t green, uint8_t blue, float alpha) : red(red), green(green), blue(blue), alpha(alpha) {}
};

class Sprite {
public:
    int width;
    int height;

    Sprite(int width, int height, const char* data);
    Sprite(const char* filename, bool withAlpha = true);
    Sprite(const CImg<unsigned char>& image, bool withAlpha = true);
    Pixel getPixel(int x, int y) const;

private:
    vector<Pixel> matrix;
    void loadImage(const CImg<unsigned char>& image, bool withAlpha);
    CImgDisplay dsp;
};


class RGBAMatrix
{
public:
    int width;
    int height;

    RGBAMatrix(int width, int height, const Pixel& background=Pixel());
    void clear(const Pixel& background=Pixel());

    Pixel getPixel(int x, int y) const;
    void setPixel(int x, int y, const Pixel& pixel);
    void addPixel(int x, int y, const Pixel& pixel);
    void addSprite(int x, int y, const Sprite& sprite);

    void drawCircle(int x, int y, int radius, const Pixel& pixel);
    void drawRing(int x, int y, int radius1, int radius2, const Pixel& pixel);

    void writeToCanvas(Canvas* canvas) const;

private:
    vector<Pixel> matrix;
};

#endif // SCREEN_H
