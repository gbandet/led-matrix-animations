#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include "canvas.h"

using namespace rgb_matrix;

class SnakeTransformer : public CanvasTransformer {
public:
    SnakeTransformer(int lines, int panel_width);
    ~SnakeTransformer();

    virtual Canvas* Transform(Canvas* output);

private:
    class TransformCanvas;

    TransformCanvas* canvas;
};

class SnakeTransformer::TransformCanvas : public Canvas {
public:
    TransformCanvas(int lines, int panel_width) : lines(lines), panel_width(panel_width), delegatee(0) {}

    void SetDelegatee(Canvas* delegatee);

    virtual void Clear();
    virtual void Fill(uint8_t red, uint8_t green, uint8_t blue);
    virtual int width() const { return m_width; }
    virtual int height() const { return m_height; }
    virtual void SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue);

private:
    const int lines;
    const int panel_width;
    int m_width;
    int m_height;
    int panel_height;
    int panels_per_line;
    Canvas* delegatee;
};

#endif // TRANSFORMER_H
