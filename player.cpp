#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "animation.h"
#include "player.h"

using namespace sf;
using namespace std;

//##############
//###        ###
//### Player ###
//###        ###
//##############

//### constructor
Player::Player()
    : x(0), y(0), w(0), h(0), ismoving(false)
{
    if(this->rect==NULL)
        this->rect=new RectangleShape;
    if(this->animation==NULL)
        this->animation=new Animation;
}

//### constructor | with args
Player::Player(Texture *texture,int x,int y,int w,int h,float speed)
    : x(x), y(y), w(w), h(h), speed(speed), ismoving(false)
{
    this->rect=new RectangleShape;
    this->rect->setPosition(Vector2f(x,y));
    this->rect->setPosition(Vector2f(w,h));
    this->rect->setTexture(texture);

    this->animation=new Animation(PLAYER_ANIM_WALK_NAME_DEFAULT,3,texture,PLAYER_ANIM_WALK_FRAMES_DEFAULT,PLAYER_ANIM_WALK_SPEED_DEFAULT);
    this->animation->setFrameOptions(0,0,26,44);
    this->animation->setType(ANIM_TYPEREPEAT);
}

//### update | update func
void Player::update(float time){
    //if player stop moving, play idle animation and reset moving directions
    this->animation->update(time);
    if(this->ismoving){
        this->x+=this->dirx*this->speed*time;
        this->y+=this->diry*this->speed*time;
    }
}

void Player::move(int dirx,int diry)
{
    if(diry!=0){
        this->diry=diry;
        if(this->diry==-1)
            this->animation->setFrameOptions_pos(0,44);
        else{
            this->animation->setFrameOptions_pos(0,0);
        }
    }
    if(dirx==0 && diry==0){
        this->ismoving=false;
        this->animation->stopAnim();
        this->animation->setFrame(0);
    }
    else{
        if(!this->ismoving){
            this->animation->startAnim();
            this->ismoving=true;
        }
    }
    this->dirx=dirx;
    this->diry=diry;
}

void Player::draw(RenderWindow *window,Camera *camera){
    this->rect->setTextureRect(this->animation->getIntRect());
    this->rect->setPosition(Vector2f(this->x+camera->x,this->y+camera->y));
    this->rect->setSize(Vector2f(this->w,this->h));
    window->draw(*(this->rect));
}



//#############
//###       ###
//### Stats ###
//###       ###
//#############
Stats::Stats()
{

}
