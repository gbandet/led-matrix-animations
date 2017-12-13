#include "led-matrix.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

#include "circles.h"
#include "colortest.h"
#include "freqhistogram.h"
#include "gif.h"
#include "snowflake.h"
#include "text.h"
#include "transformer.h"
#include "xmastree.h"

using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void loop(RGBMatrix* matrix) {
    FrameCanvas *offscreen = matrix->CreateFrameCanvas();
    offscreen->Fill(0, 0, 0);
    offscreen = matrix->SwapOnVSync(offscreen);

    //Circles animation(160, 96);
    //ColorTest animation(160, 96);
    //FreqHistogram animation(160, 96);
    //SnowflakeAnimation animation(160,96);
    //XMasTree animation(160,96);
    //ScrollingText animation(160,96);
    //PartyParrot animation(160, 96);
    Flames animation(160, 96);

    while (!interrupt_received) {
        int delay = animation.nextFrame(offscreen);
        offscreen = matrix->SwapOnVSync(offscreen);
        usleep(delay * 1000);
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
