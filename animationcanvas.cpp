#include "animationcanvas.h"

AnimationCanvas::AnimationCanvas(int width, int height)
    : m_width(width), m_height(height)
{
    matrix = new QVector<QColor> (width * height);
    Fill(0, 0, 0);
}

int AnimationCanvas::width() const
{
    return m_width;
}

int AnimationCanvas::height() const
{
    return m_height;
}

void AnimationCanvas::SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue)
{
    (*matrix)[y * m_width + x] = QColor(red, green, blue);
}

QColor AnimationCanvas::GetPixel(int x, int y) const
{
    return matrix->at(y * m_width + x);
}

void AnimationCanvas::Clear()
{
    for (int i = 0; i < m_width * m_height; i++) {
        (*matrix)[i] = QColor();
    }
}

void AnimationCanvas::Fill(uint8_t red, uint8_t green, uint8_t blue)
{
    for (int i = 0; i < m_width * m_height; i++) {
        (*matrix)[i] = QColor(red, green, blue);
    }
}
