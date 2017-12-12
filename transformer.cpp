#include <assert.h>
#include <stdio.h>
#include "transformer.h"

void SnakeTransformer::TransformCanvas::SetDelegatee(Canvas* delegatee) {
    int panel_count = delegatee->width() / panel_width;
    if (delegatee->width() % panel_width != 0) {
        fprintf(stderr, "The whole width is not divisible by the width of a panel.");
        assert(false);
    }
    if (panel_count % lines !=0) {
        fprintf(stderr, "The number of panels is not divisible by the number of lines.");
        assert(false);
    }

    this->delegatee = delegatee;
    m_width = delegatee->width() / lines;
    m_height = lines * delegatee->height();
    panels_per_line = panel_count / lines;
    panel_height = delegatee->height();
}

void SnakeTransformer::TransformCanvas::Clear() {
    delegatee->Clear();
}

void SnakeTransformer::TransformCanvas::Fill(uint8_t red, uint8_t green, uint8_t blue) {
    delegatee->Fill(red, green, blue);
}

void SnakeTransformer::TransformCanvas::SetPixel(int x, int y, uint8_t red, uint8_t green, uint8_t blue) {
    if (x < 0 || x >= m_width || y < 0 || y >= m_height)
        return;

    int col = x / panel_width;
    int row = y / panel_height;

    int panel_order = row * panels_per_line;
    int panel_inverted = false;
    if (row % 2 == 0) {
        panel_order += col;
    } else {
        panel_order += panels_per_line - col - 1;
        panel_inverted = true;
    }

    int panel_x = x % panel_width;
    int panel_y = y % panel_height;
    if (panel_inverted) {
        panel_x = panel_width - 1 - panel_x;
        panel_y = panel_height - 1 - panel_y;
    }

    int final_x = panel_width * panel_order + panel_x;
    int final_y = panel_y;
    delegatee->SetPixel(final_x, final_y, red, green, blue);
}

SnakeTransformer::SnakeTransformer(int lines, int panel_width) {
    canvas = new TransformCanvas(lines, panel_width);
}

SnakeTransformer::~SnakeTransformer() {
    delete canvas;
}

Canvas *SnakeTransformer::Transform(Canvas* output) {
    canvas->SetDelegatee(output);
    return canvas;
}
