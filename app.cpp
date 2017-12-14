#include <QGridLayout>
#include "app.h"

#include "animationcanvas.h"
#include "circles.h"
#include "colortest.h"
#include "xmastree.h"
#include "snowflake.h"
#include "freqhistogram.h"
#include "text.h"
#include "gif.h"
#include "laser.h"

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

    //animation = new Circles(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new ColorTest(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new SnowflakeAnimation(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new XMasTree(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new FreqHistogram(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new ScrollingText(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new PartyParrot(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new XmasParrot(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new Flames(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new Laser(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new SnowGif(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new SlideShow(SCREEN_WIDTH, SCREEN_HEIGHT);
    //animation = new FixedText(SCREEN_WIDTH, SCREEN_HEIGHT);
    animation = new WinterSnowGif(SCREEN_WIDTH, SCREEN_HEIGHT);

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
