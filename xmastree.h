#ifndef XMASTREE_H
#define XMASTREE_H

#include "animation.h"
#include "screen.h"

class XMasTree : public Animation
{
public:
    XMasTree(int width, int height);
    virtual int nextFrame(Canvas* canvas) override;

private:
    Sprite sprite;
};

#endif // XMASTREE_H
