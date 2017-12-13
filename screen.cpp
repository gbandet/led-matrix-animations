#include "screen.h"

using namespace cimg_library;

Sprite::Sprite(int width, int height, const char* data)
    : width(width), height(height)
{
    matrix.resize(width * height);
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            int pos = 4 * (y * width + x);
            uint8_t red = data[pos];
            uint8_t green = data[pos + 1];
            uint8_t blue = data[pos + 2];
            float alpha = (uint8_t)data[pos + 3] / 255.;
            matrix[y * width + x] = Pixel(red, green, blue, alpha);
        }
    }
}

Sprite::Sprite(const char* filename)
{
    CImg<unsigned char> image(filename);
    loadImage(image);
}

Sprite::Sprite(const CImg<unsigned char>& image)
{
    loadImage(image);
}

void Sprite::loadImage(const CImg<unsigned char>& image)
{
    width = image.width();
    height = image.height();
    matrix.resize(width * height);

    for (int x = 0; x < image.width(); x++) {
        for (int y = 0; y < image.height(); y++) {
            matrix[y * width + x] = Pixel(
                image(x, y, 0, 0), image(x, y, 0, 1), image(x, y, 0, 2), image(x, y, 0, 3) / 255.);
        }
    }
}

Pixel Sprite::getPixel(int x, int y) const
{
    return matrix[y * width + x];
}


RGBAMatrix::RGBAMatrix(int width, int height, const Pixel& background)
    : width(width), height(height)
{
    clear(background);
}

void RGBAMatrix::clear(const Pixel& background)
{
    matrix.resize(width * height, background);
}

Pixel RGBAMatrix::getPixel(int x, int y) const
{
    return matrix[y * width + x];
}

void RGBAMatrix::setPixel(int x, int y, const Pixel& pixel)
{
    matrix[y * width + x] = pixel;
}

void RGBAMatrix::addPixel(int x, int y, const Pixel& pixel)
{
    Pixel current = getPixel(x, y);
    Pixel next;

    next.alpha = pixel.alpha + current.alpha * (1 - pixel.alpha);
    next.red = (pixel.alpha * pixel.red + current.alpha * current.red * (1 - pixel.alpha)) / next.alpha;
    next.green = (pixel.alpha * pixel.green + current.alpha * current.green * (1 - pixel.alpha)) / next.alpha;
    next.blue = (pixel.alpha * pixel.blue + current.alpha * current.blue * (1 - pixel.alpha)) / next.alpha;

    setPixel(x, y, next);
}

void RGBAMatrix::addSprite(int x, int y, const Sprite& sprite)
{
    for (int sprite_x = 0; sprite_x < sprite.width; sprite_x++) {
        for (int sprite_y = 0; sprite_y < sprite.height; sprite_y++) {
            int posx = x + sprite_x;
            int posy = y + sprite_y;
            if (posx < 0 || posx >= width || posy < 0 || posy >= height)
                continue;

            addPixel(posx, posy, sprite.getPixel(sprite_x, sprite_y));
        }
    }
}

void RGBAMatrix::writeToCanvas(Canvas* canvas) const
{
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            Pixel pixel = getPixel(x, y);
            canvas->SetPixel(x, y, pixel.red , pixel.green, pixel.blue);
        }
    }
}

void RGBAMatrix::drawCircle(int x, int y, int radius, const Pixel& pixel) {
    int dx = radius;
    int dy = 0;
    int radiusError = 1 - dx;

    while (dy <= dx) {
        addPixel(dx + x, dy + y, pixel);
        addPixel(dy + x, dx + y, pixel);
        addPixel(-dx + x, dy + y, pixel);
        addPixel(-dy + x, dx + y, pixel);
        addPixel(-dx + x, -dy + y, pixel);
        addPixel(-dy + x, -dx + y, pixel);
        addPixel(dx + x, -dy + y, pixel);
        addPixel(dy + x, -dx + y, pixel);

        dy++;
        if (radiusError < 0) {
            radiusError += 2 * dy + 1;
        } else {
            dx--;
            radiusError += 2 * (dy - dx + 1);
        }
    }
}


void RGBAMatrix::drawRing(int x, int y, int radius1, int radius2, const Pixel& pixel)
{
    if (radius1 > radius2) {
        int tmp = radius1;
        radius1 = radius2;
        radius2 = tmp;
    }

    int dx1 = radius1;
    int dy = 0;
    int dx2 = radius2;
    int radiusError1 = 1 - dx1;
    int radiusError2 = 1 - dx2;

    while (dy <= dx1 || dy <= dx2) {
        bool continue1 = dy <= dx1;
        bool continue2 = dy <= dx2;
        for (int offset = dx1; offset <= dx2; offset++) {
            addPixel(offset + x, dy + y, pixel);
            addPixel(dy + x, offset + y, pixel);
            addPixel(-offset + x, dy + y, pixel);
            addPixel(-dy + x, offset + y, pixel);
            addPixel(-offset + x, -dy + y, pixel);
            addPixel(-dy + x, -offset + y, pixel);
            addPixel(offset + x, -dy + y, pixel);
            addPixel(dy + x, -offset + y, pixel);
        }
        dy++;
        if (continue1) {
            if (radiusError1 < 0) {
                radiusError1 += 2 * dy + 1;
            } else {
                dx1--;
                radiusError1 += 2 * (dy - dx1 + 1);
            }
        }
        if (continue2) {
            if (radiusError2 < 0) {
                radiusError2 += 2 * dy + 1;
            } else {
                dx2--;
                radiusError2 += 2 * (dy - dx2 + 1);
            }
        }
    }
}
