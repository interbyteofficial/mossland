#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "obj_static.h"
#include "camera.h"
#include "animation.h"
#include "particle.h"
#include "random.h"
#include "error.h"

using namespace sf;
using namespace std;

inline bool collideRect(int x,int y,int w,int h,int mx,int my){
    return (mx>=x && my>=y && mx<=x+w && my<=y+h)? true : false;
}

bool collideRectIn(int x,int y,int w,int h,int mx,int my){
    return (mx>x && my>y && mx<x+w && my<y+h)? true : false;
}

void ObjectStatic::updateMousepos(int mx,int my,Camera *camera){
    this->mouseover=collideRect(this->x,this->y,this->w,this->h,mx+camera->x,my+camera->y);
}

void ObjectStatic::draw(RenderWindow *window,Camera *camera)
{
    try{
        if(this->rect==NULL)
            throw "[ObjectStatic] Memory leak! ObjectStatic::rect can't equal NULL";
        window->draw(*(this->rect));
    }
    catch(string error){
        errorRaise(error);
    }
}

void ObjectStatic::update(float time)
{
    this->rect->setPosition(Vector2f(this->x,this->y));
    this->rect->setSize(Vector2f(this->x,this->y));
    this->rect->setTextureRect(this->anim->getIntRect());

    this->anim->update(time);
}
ObjectStatic::ObjectStatic()
    : x(0), y(0), w(0), h(0), deleted(false)
{

}

ObjectStatic::ObjectStatic(float x,float y,float w,float h,Texture *texture,Animation *anim,string name,int id)
    : x(x), y(y), w(w), h(h), deleted(false)
{
    this->rect=new RectangleShape(Vector2f(w,h));
    this->rect->setPosition(Vector2f(x,y));
    this->rect->setTexture(texture);
    this->anim=anim;
}

//### setters ###
void ObjectStatic::setPosition(float x,float y){
    this->x=x;
    this->y=y;
}

void ObjectStatic::setSize(float w,float h){
    this->w=w;
    this->h=h;
}

void ObjectStatic::setSolid(bool state){
    this->solid=state;
}

void ObjectStatic::setVisible(bool state){
    this->visible=state;
}

void ObjectStatic::setDeleted(bool state){
    this->deleted=state;
}

//### getters ###
bool ObjectStatic::isMouseover(){
    return this->mouseover;
}
bool ObjectStatic::isDeleted(){
    return this->deleted;
}
bool ObjectStatic::isSolid(){
    return this->solid;
}
Vector2f ObjectStatic::getSize(){
    return Vector2f(this->w,this->h);
}
Vector2f ObjectStatic::getPosition(){
    return Vector2f(this->x,this->y);
}
//###
//### ObjectResource
//###

//### CONSTRUCTORS
ObjectResource::ObjectResource()
{

}
ObjectResource::ObjectResource(string name,int id)
    : ObjectStatic(),destroyed(false),maxframe(0)
{
    this->rect=new RectangleShape;
    this->deleted=false;
    this->name=name;
    this->id=id;
}
ObjectResource::ObjectResource(string name,int id,int hp,int maxframe,Texture *texture,Animation *anim)
    : ObjectStatic(0,0,0,0,texture,anim,name,id), maxframe(maxframe), destroyed(false), hp(hp), maxhp(hp)
{
    this->rect=new RectangleShape;
    this->rect->setTexture(texture);
    this->anim=anim;
    this->rect->setTextureRect(this->anim->getIntRect());
}
//### DESTRUCTORS ###
ObjectResource::~ObjectResource()
{
    if(this->anim!=NULL)
        delete this->anim;
    if(this->prtemm_kick!=NULL)
        delete this->prtemm_kick;
    if(this->prtemm_destroy!=NULL)
        delete this->prtemm_destroy;
}
//### SETTERS ###
void ObjectResource::setStats(int hp)
{
    this->hp=hp;
    this->maxhp=hp;
}
void ObjectResource::setPosition(float x,float y)
{
    try{
        if(this->prtemm_kick==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_kick can't equal NULL";
        if(this->prtemm_destroy==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_destroy can't equal NULL";
        this->x=x;
        this->y=y;
        this->prtemm_destroy->setPosition(x,y);
        this->prtemm_kick->setPosition(x,y);
    }
    catch(string error){
        errorRaise(error);
    }
}

void ObjectResource::setSize(float w,float h)
{
    try{
        if(this->prtemm_kick==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_kick can't equal NULL";
        if(this->prtemm_destroy==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_destroy can't equal NULL";
        this->w=w;
        this->h=h;
        this->prtemm_destroy->setPosition(x+this->w/2,y+this->h/2);
        this->prtemm_kick->setPosition(x,y);
    }
    catch(string error){
        errorRaise(error);
    }
}

void ObjectResource::setParticles(ParticleEmmiter *prtemm_kick, ParticleEmmiter *prtemm_destroy)
{
    this->prtemm_kick=prtemm_kick;
    this->prtemm_destroy=prtemm_destroy;
}

//### MAIN ###
void ObjectResource::mouseClick(int mx,int my,float power,Camera *camera)
{
    try{
        if(this->prtemm_kick==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_kick can't equal NULL";
        if(this->anim==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::anim can't equal NULL";
        if(this->mouseover && this->hp>0 && !this->destroyed && !this->deleted){
            this->hp-=power;
            this->prtemm_kick->setPosition(mx+camera->x,my+camera->y);
            //this->prtemm_kick->setPosition(mx,my);
            this->prtemm_kick->createParticles(15,0.05,0.07,0.3,0.6,PARTICLE_DEC_DEFAULT,PARTICLE_GRAVITY_DEFAULT);
            this->anim->setFrame(this->anim->getMaxframe()-int(this->hp/float(this->maxhp/this->anim->getMaxframe()))-1);
        }
    }
    catch(string error){
        errorRaise(error);
    }

}

void ObjectResource::update(float time,Camera *camera)
{
    try{
        if(this->prtemm_kick==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_kick can't equal NULL";
        if(this->prtemm_destroy==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_destroy can't equal NULL";
        if(this->anim==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::anim can't equal NULL";
        if(int(this->hp)==0 && !this->destroyed){
            //this->prtemm_destroy->addPosition(camera->y,camera->x);
            //this->prtemm_destroy->setPosition(this->x,this->y);
            this->prtemm_destroy->createParticles(30,0.05,0.1,0.4,0.6,PARTICLE_DEC_DEFAULT,PARTICLE_GRAVITY_DEFAULT);
            this->destroyed=true;
            this->solid=false;
        }
        if(!this->deleted && this->destroyed && this->prtemm_destroy->getCount()==0){
            this->deleted=true;
        }
        this->anim->update(time);
        this->prtemm_destroy->update(time);
        this->prtemm_kick->update(time);
    }
    catch(string error){
        errorRaise(error);
    }
}

void ObjectResource::draw(RenderWindow *window,Camera *camera)
{
    try{
        if(this->prtemm_kick==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_kick can't equal NULL";
        if(this->prtemm_destroy==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::prtemm_destroy can't equal NULL";
        if(this->rect==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::rect can't equal NULL";
        if(this->anim==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::anim can't equal NULL";

        if(!this->destroyed && !this->deleted){
            this->rect->setPosition(Vector2f(this->x-camera->x,this->y-camera->y));
            this->rect->setSize(Vector2f(this->w,this->h));
            this->rect->setTextureRect(this->anim->getIntRect());
            window->draw(*(this->rect));
        }
        this->prtemm_kick->draw(window,camera);
        this->prtemm_destroy->draw(window,camera);
    }
    catch(string error){
        errorRaise(error);
    }
}

//### GEN ###
void ObjectResource::genAnim(int maxframe,float speed,IntRect intrect,Texture *texture)
{
    Texture *textureanim=(texture==NULL)? this->texture : texture;
    this->anim=new Animation("objr_stone",0,this->texture,maxframe,speed);
    this->anim->setFrameOptions(intrect.left,intrect.top,intrect.width,intrect.height);
    this->anim->setType(ANIM_TYPEREPEAT);
}

void ObjectResource::genParticleKick(int w,int h,IntRect intrect,Texture *texture)
{
    Texture *textureprtemm=(texture==NULL)? this->texture : texture;
    this->rect_prtemm_kick=new RectangleShape(Vector2f(w,h));
    this->rect_prtemm_kick->setTexture(this->texture);

    this->rect_prtemm_kick->setTextureRect(intrect);
    this->prtemm_kick=new ParticleEmmiter(this->x+this->w/2,this->y+this->h/2,w,h,this->rect_prtemm_kick);
}

void ObjectResource::genParticleDestroy(int w,int h,IntRect intrect,Texture *texture)
{
    Texture *textureprtemm=(texture==NULL)? this->texture : texture;
    this->rect_prtemm_destroy=new RectangleShape(Vector2f(w,h));
    this->rect_prtemm_destroy->setTexture(this->texture);

    this->rect_prtemm_destroy->setTextureRect(intrect);
    this->prtemm_destroy=new ParticleEmmiter(this->x,this->y,w,h,this->rect_prtemm_destroy);
}

void ObjectResource::setTexture(Texture *texture)
{
    try{
        if(this->rect==NULL)
            throw "[ObjectResource] Memory leak! ObjectResource::rect can't equal NULL";
        this->texture=texture;
        this->rect->setTexture(texture);
    }
    catch(string error){
        errorRaise(error);
    }
}

//### GETTERS ###
float ObjectResource::getHp(){
    return this->hp;
}
float ObjectResource::getMaxhp(){
    return this->maxhp;
}
