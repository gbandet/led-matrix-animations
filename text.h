#ifndef TEXT_H
#define TEXT_H

#include <string>
#include <vector>
#include "animation.h"
#include "graphics.h"

using namespace std;

class ScrollingText : public Animation
{
public:
    ScrollingText(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;
    void changeSentence();

private:
    vector<string> sentences;
    rgb_matrix::Font font;
    string current_text;
    int current_x;
    int current_y;
    Color current_color;
};

#endif // TEXT_H
