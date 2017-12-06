#include <QGridLayout>
#include "app.h"

#include "animationcanvas.h"
#include "colortest.h"

App::App(QWidget *parent) : QWidget(parent)
{
    renderArea = new RenderArea;

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(renderArea, 0, 0);
    setLayout(layout);

    currentFrame = new AnimationCanvas(128, 96);
    currentFrame->Fill(0, 0, 0);
    renderArea->setCanvas(currentFrame);

    animation = new ColorTest(128, 96);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(0);
}

App::~App() {}

void App::nextFrame()
{
    AnimationCanvas* newFrame = new AnimationCanvas(128, 96);

    int delay = animation->nextFrame(newFrame);
    timer->setInterval(delay);

    renderArea->setCanvas(newFrame);
    delete currentFrame;
    currentFrame = newFrame;
}
