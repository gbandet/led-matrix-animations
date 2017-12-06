#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include "animationcanvas.h"

class RenderArea : public QWidget
{
    Q_OBJECT
public:
    explicit RenderArea(QWidget *parent = 0);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    void setCanvas(AnimationCanvas*);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    AnimationCanvas* canvas;
};

#endif // RENDERAREA_H
