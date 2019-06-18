#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "animation.h"
#include "player.h"
#include "obj_static.h"

using namespace sf;
using namespace std;

//##############
//###        ###
//### Player ###
//###        ###
//##############

//### constructor
Player::Player()
    : x(0), y(0), w(0), h(0), ismoving(false), tempx(0), tempy(0)
{
    if(this->rect==NULL)
        this->rect=new RectangleShape;
    if(this->animation==NULL)
        this->animation=new Animation;
}

//### constructor | with args
Player::Player(Texture *texture,int x,int y,int w,int h,float speed)
    : x(x), y(y), w(w), h(h), speed(speed), ismoving(false), tempx(x), tempy(y)
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

void Player::update(float time,vector<ObjectStatic*> vector_objs_solid,Camera *camera){
    //if player stop moving, play idle animation and reset moving directions
    this->animation->update(time);
    if(this->ismoving){
        this->x+=this->dirx*this->speed*time;
        this->y+=this->diry*this->speed*time;
    }
    if(this->checkCollision(this->dirx*time,0,vector_objs_solid,camera)){
        this->x=this->tempx;
    }
    else{
        this->tempx=this->x;
    }
    if(this->checkCollision(0,this->diry*time,vector_objs_solid,camera)){
        this->y=this->tempy;
    }
    else{
        this->tempy=this->y;
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
    this->rect->setPosition(Vector2f(this->x-(int)camera->x,this->y-(int)camera->y));
    this->rect->setSize(Vector2f(this->w,this->h));
    window->draw(*(this->rect));
}

bool Player::checkCollision(float dirx,float dir,vector<ObjectStatic*> vector_objs,Camera *camera)
{
    int newx=this->x+this->speed*dirx;
    int newy=this->y+this->speed*diry;
    for(auto it : vector_objs)
    {
        if(it->isSolid()){
//            if(collideRectIn(it->getPosition().x,it->getPosition().y,it->getSize().x,it->getSize().y,newx,newy))
//                return true;
//            if(collideRectIn(it->getPosition().x,it->getPosition().y,it->getSize().x,it->getSize().y,newx+this->w,newy))
//                return true;
//            if(collideRectIn(it->getPosition().x,it->getPosition().y,it->getSize().x,it->getSize().y,newx+this->w,newy+this->h))
//                return true;
//            if(collideRectIn(it->getPosition().x,it->getPosition().y,it->getSize().x,it->getSize().y,newx,newy+this->h))
//                return true;
            if(IntRect(newx-camera->x,newy-camera->y,this->w,this->h).intersects(IntRect(it->getPosition().x-camera->x,it->getPosition().y-camera->y,it->getSize().x,it->getSize().y)))
                return true;
        }
    }
    return false;
}
//### getters ###
Vector2f Player::getPosition(){
    return Vector2f(this->x,this->y);
}
Vector2f Player::getSize(){
    return Vector2f(this->w,this->h);
}
//#############
//###       ###
//### Stats ###
//###       ###
//#############
Stats::Stats()
{

}
