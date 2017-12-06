#ifndef APP_H
#define APP_H

#include <QTimer>
#include <QWidget>
#include "animation.h"
#include "renderarea.h"

class App : public QWidget
{
    Q_OBJECT

    RenderArea* renderArea;
    QTimer* timer;
    AnimationCanvas* currentFrame;
    AnimationCanvas* newFrame;
    Animation* animation;

public:
    App(QWidget *parent = 0);
    ~App();

public slots:
    void nextFrame();
};

#endif // APP_H
