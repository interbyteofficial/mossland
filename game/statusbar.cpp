#include <SFML/Graphics.hpp>
#include <iostream>
#include "statusbar.h"

using namespace sf;
using namespace std;

//### CONSTRUCTORS ###
StatusBar::StatusBar()
    : name(""), id(-1), visible(false), deleted(false)
{

}

StatusBar::StatusBar(string name,int id)
    : name(name), id(id), visible(false), deleted(false)
{

}

StatusBar::StatusBar(string name,int id,int x,int y,int w,int h,float max,float value,Color color1,Color color2,Color color3,int border)
    : name(name), id(id), visible(true), deleted(false)
{
    this->rectin=new RectangleShape;
    this->rectout=new RectangleShape;
    this->setPosition(x,y);
    this->setSize(w,h,border);
    this->setValue(value);
    this->setMaxvalue(max);
    this->setColors(color1,color2,color3);
}

//### SETTERS ###
void StatusBar::setPosition(int x,int y)
{
    this->x=x;
    this->y=y;
    this->rectout->setPosition(Vector2f(x,y));
    this->rectin->setPosition(Vector2f(x,y));
}

void StatusBar::setSize(float w,float h,float border)
{
    this->border=border;
    this->w=w;
    this->h=h;
    this->rectout->setSize(Vector2f(w,h));
    this->rectin->setSize(Vector2f(w/this->max*this->value,h));
    this->rectout->setOutlineThickness(this->border);
}

void StatusBar::setValue(float value)
{
    this->value=value;
    if(value<=0){
        this->rectin->setSize(Vector2f(0,0));
        return;
    }
    this->rectin->setSize(Vector2f(w/this->max*this->value,h));
}

void StatusBar::setMaxvalue(float maxvalue)
{
    this->max=maxvalue;
    this->rectin->setSize(Vector2f(w/this->max*this->value,h));
}

void StatusBar::setColors(Color colormain,Color colorbg,Color colorborder)
{
    this->color1=colormain;
    this->color2=colorbg;
    this->color3=colorborder;

    this->rectin->setFillColor(this->color1);
    this->rectout->setFillColor(this->color2);
    this->rectout->setOutlineColor(this->color3);
}

void StatusBar::setBorder(float size)
{
    this->border=border;
    this->rectout->setOutlineThickness(this->border);
}

void StatusBar::setVisible(bool state)
{
    this->visible=state;
}

void StatusBar::setDeleted(bool state)
{
    this->deleted=state;
}

//### GETTERS ###
Vector2f StatusBar::getPosition()
{
    return Vector2f(this->x,this->y);
}
Vector2f StatusBar::getSize()
{
    return Vector2f(this->w,this->h);
}
//### UPDATE ###
void StatusBar::update(float time)
{

}

//### DRAW ###
void StatusBar::draw(RenderWindow *window,Camera *camera)
{
    if(!this->visible){
        return;
    }
    this->rectin->setPosition(Vector2f(this->x-camera->x,this->y-camera->y));
    this->rectout->setPosition(Vector2f(this->x-camera->x,this->y-camera->y));
    cout<<"rectout x:"<<this->rectout->getPosition().x<<" y:"<<this->rectout->getPosition().y<<endl;
    cout<<"rectout w:"<<this->rectout->getSize().x<<" h:"<<this->rectout->getSize().y<<endl;
    window->draw(*(this->rectout));
    window->draw(*(this->rectin));
}
