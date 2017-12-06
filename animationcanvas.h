#ifndef ANIMATIONCANVAS_H
#define ANIMATIONCANVAS_H

#include <QColor>
#include <QVector>
#include "canvas.h"

using namespace rgb_matrix;

class AnimationCanvas : public Canvas
{
public:
    AnimationCanvas(int width, int height);

    virtual int width() const;
    virtual int height() const;
    virtual QColor GetPixel(int x, int y) const;
    virtual void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);
    virtual void Clear();
    virtual void Fill(uint8_t red, uint8_t green, uint8_t blue);

private:
    int m_width;
    int m_height;

    QVector<QColor>* matrix;
};

#endif // ANIMATIONCANVAS_H
