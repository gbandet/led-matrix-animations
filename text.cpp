#include "text.h"
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace rgb_matrix;

const int TEXT_SPEED = 3;
const int VERTICAL_MARGIN = 30;
const int FONT_HEIGHT = 20;
const int FONT_WIDTH = 10;

ScrollingText::ScrollingText(int width, int height)
    : Animation(width, height), current_color(0, 0, 0)
{
    font.LoadFont("assets/fonts/10x20.bdf");
    std::ifstream file("assets/sentences.txt");
    std::string line;
    while (std::getline(file, line)){
        sentences.push_back(line);
    }
    changeSentence();
}


int ScrollingText::nextFrame(Canvas* canvas)
{
    canvas->Fill(0, 0, 0);
    DrawText(canvas, font, current_x, current_y, current_color, 0, current_text.c_str());
    current_x -= TEXT_SPEED;
    if (current_x + FONT_WIDTH * (int)current_text.length() < 0) {
        changeSentence();
    }
    return 40;
}

void ScrollingText::changeSentence()
{
    current_text = sentences[rand() % sentences.size()];
    current_x = width;
    current_y = (rand() % (height - 2 * VERTICAL_MARGIN)) + VERTICAL_MARGIN;
    current_color = Color(rand() % 255, rand() % 255, rand() % 255);
}

FixedText::FixedText(int width, int height)
    : Animation(width, height), text("Winter 2017")
{
    font.LoadFont("assets/fonts/10x20.bdf");
}

int FixedText::nextFrame(Canvas* canvas)
{
    canvas->Fill(0, 0, 0);
    DrawText(canvas, font, 25, 58, Color(255, 0, 0), 0, text.c_str());
    return 500;
}
