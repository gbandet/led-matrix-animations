#include <QPainter>
#include "renderarea.h"

RenderArea::RenderArea(QWidget *parent) : QWidget(parent), canvas(0)
{}

QSize RenderArea::minimumSizeHint() const
{
    if (!canvas)
        return QSize(0, 0);
    return QSize(canvas->width(), canvas->height());
}

QSize RenderArea::sizeHint() const
{
    if (!canvas)
        return QSize(0, 0);
    return QSize(canvas->width(), canvas->height());
}

void RenderArea::setCanvas(AnimationCanvas* canvas)
{
    this->canvas = canvas;
    update();
}

void RenderArea::paintEvent(QPaintEvent* /* event */)
{
    if (!canvas)
        return;

    QPainter painter(this);
    painter.fillRect(0, 0, canvas->width(), canvas->height(), Qt::SolidPattern);
    for (int x = 0; x < canvas->width(); x++) {
        for (int y = 0; y < canvas->height(); y++) {
            QColor color = canvas->GetPixel(x, y);
            painter.setPen(color);
            painter.drawPoint(x, y);
        }
    }
}
