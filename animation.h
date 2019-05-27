#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#define ANIM_TYPEONCE 0
#define ANIM_TYPEREPEAT 1
#define ANIM_TYPEBOUNCE 2

using namespace sf;
using namespace std;

class Animation
{
private:
    float frame;
    float framespeed;
    int maxframe;
    int framex,framey;
    int framew,frameh;
    Sprite *sprite=NULL;

    bool play;
    int type;
    string name;
    int id;
public:
    Animation();
    Animation(string name, int id, Texture *texture, int maxframe, float framespeed);
    void setFrameOptions(int x,int y,int w,int h);
    void update(float time);
    void play();
    void stop();
    void setType(int type);
    Sprite* getSprite();
};

#endif // ANIMATION_H_INCLUDED
