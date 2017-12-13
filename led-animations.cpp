#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <map>
#include <fstream>

#include "animation.h"
#include "circles.h"
#include "colortest.h"
#include "freqhistogram.h"
#include "gif.h"
#include "snowflake.h"
#include "text.h"
#include "transformer.h"
#include "xmastree.h"

using namespace std;
using namespace rgb_matrix;

const int SCREEN_WIDTH = 160;
const int SCREEN_HEIGHT = 96;
const char* DEFAULT_ANIMATION = "text";
const int ANIMATION_REFRESH_TIMER = 1000;
const char* CMD_FILENAME = "animation.cmd";

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static map<string, Animation*> getAnimations() {
    map<string, Animation*> animations;
    animations["test"] = new ColorTest(SCREEN_WIDTH, SCREEN_HEIGHT);
    animations["music"] = new FreqHistogram(SCREEN_WIDTH, SCREEN_HEIGHT);
    animations["snowflake"] = new SnowflakeAnimation(SCREEN_WIDTH, SCREEN_HEIGHT);
    animations["xmas"] = new XMasTree(SCREEN_WIDTH, SCREEN_HEIGHT);
    animations["text"] = new ScrollingText(SCREEN_WIDTH, SCREEN_HEIGHT);
    animations["parrot"] = new PartyParrot(SCREEN_WIDTH, SCREEN_HEIGHT);
    animations["flames"] = new Flames(SCREEN_WIDTH, SCREEN_HEIGHT);
    return animations;
}

static string readAnimation() {
    ifstream file(CMD_FILENAME);
    string line;
    if (getline(file, line)) {
        return line;
    }
    return "";
}

static void loop(RGBMatrix* matrix) {
    FrameCanvas *offscreen = matrix->CreateFrameCanvas();
    offscreen->Fill(0, 0, 0);
    offscreen = matrix->SwapOnVSync(offscreen);

    map<string, Animation*> animations = getAnimations();

    Animation* animation = animations[DEFAULT_ANIMATION];
    string previous_name = DEFAULT_ANIMATION;
    int refresh_time = 0;

    while (!interrupt_received) {
        if (refresh_time >= ANIMATION_REFRESH_TIMER) {
            refresh_time = 0;
            string name = readAnimation();
            if (name != previous_name && animations.count(name)) {
                animation = animations[name];
                previous_name = name;
            }
        }
        int delay = animation->nextFrame(offscreen);
        offscreen = matrix->SwapOnVSync(offscreen);
        usleep(delay * 1000);
        refresh_time += delay;
    }
}

int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "adafruit-hat";
  defaults.rows = 32;
  defaults.chain_length = 15;
  defaults.parallel = 1;
  defaults.show_refresh_rate = true;
  RGBMatrix* matrix = rgb_matrix::CreateMatrixFromFlags(&argc, &argv, &defaults);
  if (!matrix)
    return 1;
  SnakeTransformer transformer(3, 32);
  matrix->ApplyStaticTransformer(transformer);

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  loop(matrix);

  matrix->Clear();
  delete matrix;
  return 0;
}
