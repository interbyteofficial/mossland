#ifndef OBJECT_H_INCLUDED
#define OBJECT_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "inventory.h"

class Object
{
protected:
    int x,y,w,h;
    RectangleShape *rect=NULL;
    bool visible;

    int id;
    string name;

public:
    Object();
    ~Object();
    Object(int x,int y,int w,int h,Texture *texture,int id,string name);
    virtual void setPosition(int x,int y);
    virtual void setSize(int ,int y);
    virtual void update();
    virtual void draw(RenderWindow *window,int camx,int camy);
};

class ObjectSource : protected Object
{
private:
    Item item_drop;
    Item item_mine;
    int dropmin;
    int dropmax;
    int hp;

    Animation *anim=NULL;
public:
    ObjectSource
    void setAnimation(int x,int y,int w,int h);
    Animation* getAnimation();
};

class ObjectItem : protected Object
{
    Item item
};

#endif // OBJECT_H_INCLUDED
