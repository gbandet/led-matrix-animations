#include <QGridLayout>
#include "app.h"

#include "animationcanvas.h"
#include "colortest.h"

static const int SCREEN_WIDTH = 160;
static const int SCREEN_HEIGHT = 96;

App::App(QWidget *parent) : QWidget(parent)
{
    renderArea = new RenderArea;

    QGridLayout* layout = new QGridLayout;
    layout->addWidget(renderArea, 0, 0);
    setLayout(layout);

    currentFrame = new AnimationCanvas(SCREEN_WIDTH, SCREEN_HEIGHT);
    currentFrame->Fill(0, 0, 0);
    renderArea->setCanvas(currentFrame);

    animation = new ColorTest(SCREEN_WIDTH, SCREEN_HEIGHT);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    timer->start(0);
}

App::~App() {}

void App::nextFrame()
{
    AnimationCanvas* newFrame = new AnimationCanvas(SCREEN_WIDTH, SCREEN_HEIGHT);

    int delay = animation->nextFrame(newFrame);
    timer->setInterval(delay);

    renderArea->setCanvas(newFrame);
    delete currentFrame;
    currentFrame = newFrame;
}
