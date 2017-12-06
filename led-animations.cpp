#include "led-matrix.h"
#include "graphics.h"

#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>

#include "colortest.h"

using namespace rgb_matrix;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void loop(RGBMatrix* matrix) {
    FrameCanvas *offscreen = matrix->CreateFrameCanvas();
    offscreen->Fill(0, 0, 0);
    offscreen = matrix->SwapOnVSync(offscreen);

     ColorTest animation(128, 96);

    while (!interrupt_received) {
        int delay = animation.nextFrame(offscreen);
        offscreen = matrix->SwapOnVSync(offscreen);
        usleep(delay);
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

  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  loop(matrix);

  matrix->Clear();
  delete matrix;
  return 0;
}
