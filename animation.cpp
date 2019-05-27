#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"

using namespace sf;
using namespace std;

Animation::Animation()
{

}

Animation::Animation(string name, int id, Texture *texture, int maxframe, float framespeed)
    : name(name), id(id), maxframe(maxframe), framespeed(framespeed), frame(0), play(false)
{
    this->rect->setTexture(*texture);
}

void Animation::setFrameOptions(int x, int y, int w, int h)
    : framex(x), framey(y), framew(w), frameh(h)
{
    this->sprite->getTextureRect(x,y,w,h);
}

void
