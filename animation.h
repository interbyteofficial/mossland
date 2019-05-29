#ifndef ANIMATION_H_INCLUDED
#define ANIMATION_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#define ANIM_TYPEONCE 0
#define ANIM_TYPEREPEAT 1
#define ANIM_TYPEBOUNCE 2
#define ANIM_TYPEONCEHIDE 3

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
    RectangleShape *rect=NULL;

    bool play;
    bool show;
    int type;

    string name;
    int id;
public:
    //### constructors ###
    Animation();
    Animation(string name, int id, Texture *texture, int maxframe, float framespeed);

    //### update ###
    void update(float time);

    //### control anim ###
    void startAnim();
    void playAnim();
    void pauseAnim();
    void stopAnim();
    void showAnim();
    void hideAnim();

    //### setters ###
    void setFrameOptions(int x,int y,int w,int h);
    void setType(int type);
    void setFrame(float frame);
    void setFrameOptions_pos(int x,int y);

    //### getters ###
    Texture* getTexture();
    const RectangleShape* getRect();
    RectangleShape* getRectPointer();
    IntRect getIntRect();
};

#endif // ANIMATION_H_INCLUDED
