#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"

using namespace sf;
using namespace std;

Animation::Animation()
    : name(""), id(0), maxframe(0), framespeed(0), frame(0), play(false)
{

}

Animation::Animation(string name, int id, Texture *texture, int maxframe, float framespeed)
    : name(name), id(id), maxframe(maxframe), framespeed(framespeed), frame(0), play(false)
{
    this->rect=new RectangleShape;
    this->rect->setTexture(texture);
}

void Animation::setFrameOptions(int x, int y, int w, int h)
{
    this->framex=x;
    this->framey=y;
    this->framew=w;
    this->frameh=h;
    this->rect->setTextureRect(IntRect(x,y,w,h));
}

void Animation::update(float time)
{
    if(this->play)
        this->frame+=time*this->framespeed;

    if(int(this->frame)>=this->maxframe){
        switch(this->type){
            case ANIM_TYPEBOUNCE:
                this->framespeed*=-1;
                break;
            case ANIM_TYPEREPEAT:
                this->frame=0;
                break;
            case ANIM_TYPEONCE:
                this->play=false;
                break;
            case ANIM_TYPEONCEHIDE:
                this->play=false;
                this->hideAnim();
        }
    }
    if(this->frame<0)
    {
        if(this->type==ANIM_TYPEBOUNCE){
            this->framespeed*=-1;
        }
    }
    //this->rect->setTextureRect(IntRect(this->framex+int(this->frame)*this->framew,this->framey,this->framew,this->frameh));
}

//###
//### Anim constrol
//###
void Animation::startAnim(){
    this->frame=0;
    this->play=true;
    this->rect->setTextureRect(IntRect(this->framex+int(this->frame)*this->framew,this->framey,this->framew,this->frameh));
}
void Animation::playAnim(){
    this->play=true;
}

void Animation::pauseAnim(){
    this->play=false;
}

void Animation::stopAnim(){
    this->play=false;
    this->frame=0;
}

void Animation::showAnim(){
    this->show=true;
}

void Animation::hideAnim(){
    this->show=false;
}

//###
//### setters
//###
void Animation::setType(int type){
    this->type=type;
}

void Animation::setFrame(float frame){
    this->frame=frame;
    this->update(0);
}

void Animation::setFrameOptions_pos(int x,int y)
{
    this->framex=x;
    this->framey=y;
    this->update(0);
}

//###
//### getters
//###
Texture* Animation::getTexture()
{
    if(this->show && this->rect!=NULL){
        return const_cast<Texture*>(this->rect->getTexture());
    }
}

const RectangleShape* Animation::getRect()
{
    return const_cast<const RectangleShape*>(this->rect);
}

RectangleShape* Animation::getRectPointer()
{
    this->rect->setTextureRect(IntRect(this->framex+int(this->frame)*this->framew,this->framey,this->framew,this->frameh));
    return this->rect;
}

IntRect Animation::getIntRect()
{
    return IntRect(this->framex+int(this->frame)*this->framew,this->framey,this->framew,this->frameh);
    cout<<"frame: "<<this->frame<<endl;
}
