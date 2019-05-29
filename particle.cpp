#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <math.h>
#include "particle.h"
#include "random.h"

using namespace sf;
using namespace std;

//########################
//###                  ###
//### ParticleEmmiter  ###
//###                  ###
//########################

//###
//### constructor | class constructor
//###
ParticleEmmiter::ParticleEmmiter()
    : x(0), y(0), w(0), h(0), gravityspeed(0)
{
    if(this->rect==NULL)
        this->rect=new RectangleShape;
}

//###
//### constructor | class constructor (with arguments)
//###
ParticleEmmiter::ParticleEmmiter(int x,int y,int w,int h,RectangleShape *rect)
    : x(x), y(y), w(w), h(h), gravityspeed(0)
{
    this->rect=rect;
    this->rect->setPosition(Vector2f(x,y));
    this->rect->setSize(Vector2f(w,h));
}

//###
//### destructor | class destructor
//###
ParticleEmmiter::~ParticleEmmiter()
{
    this->clear();
    delete (this->rect);
}

//###
//### clear | clear all particles
//###
void ParticleEmmiter::clear()
{
    while(this->vector_particles.size()>0)
    {
        auto it=this->vector_particles.begin();
        this->vector_particles.erase(it);
        delete *it;
    }
}

//###
//### createParticles | Function to create some new particles (with rectangleshape)
//###
void ParticleEmmiter::createParticles(int num,float speed,float speedmax,float alphaspeed,float alphaspeedmax,float decspeed,float gravityspeed)
{
    this->decspeed=decspeed;
    this->gravityspeed=gravityspeed;

    this->rect->setPosition(Vector2f(this->x,this->y));
    this->rect->setSize(Vector2f(this->w,this->h));

    for(int i=0; i<num; i++){
        float angle=random(0,360);
        cout<<"part speed: "<<randomf(speed,speedmax)<<endl;
        cout<<"part alphaspeed: "<<randomf(alphaspeed,alphaspeedmax)<<endl;
        Particle *particle=new Particle(x,y,cos(angle),sin(angle),randomf(speed,speedmax),randomf(alphaspeed,alphaspeedmax),this->vector_particles.size());
        this->vector_particles.push_back(particle);
    }
}

//###
//### update | function to update particles
//###
void ParticleEmmiter::update(float time)
{
    for(int i=0; i<this->vector_particles.size(); i++){
        for(auto it=this->vector_particles.begin(); it!=this->vector_particles.end(); it++){
            //if flag are remove we delete it
            if((*it)->remove){
                delete *it;
                this->vector_particles.erase(it);
                break;
            }
        }
    }
    //if particles are
    //for each particles
    for(auto it=this->vector_particles.begin(); it!=this->vector_particles.end(); it++){
        //update particle
        (*it)->update(time);
        (*it)->speed-=this->decspeed*time;
        (*it)->speedgravity+=this->gravityspeed*time;
        //check if our particle is faded, and set remove flag to true
        if((*it)->alpha<0 || (*it)->speedgravity<=0){
            (*it)->remove=true;
        }

    }
    cout<<"size of particles:"<<this->vector_particles.size()<<endl;
}

//###
//### draw | function to draw particles
//###
void ParticleEmmiter::draw(RenderWindow *window)
{
    //for each particle
    for(auto it=this->vector_particles.begin(); it!=this->vector_particles.end(); it++)
    {
        if(!(*it)->remove){
            //set rect to options of particle
            this->rect->setPosition(Vector2f((*it)->x,(*it)->y));
            this->rect->setSize(Vector2f(this->w,this->h));
            this->rect->setFillColor(Color(rect->getFillColor().r,rect->getFillColor().g,rect->getFillColor().b,(*it)->alpha));
            window->draw(*(this->rect));
        }
    }
}

//###
//### setters | set some value in variable of class
//###
void ParticleEmmiter::setPosition(int x,int y){
    this->x=x;
    this->y=y;
}

void ParticleEmmiter::setRect(RectangleShape *rect){
    this->rect=rect;
}

//################
//###          ###
//### Particle ###
//###          ###
//################
Particle::Particle()
    : x(0), y(0), dirx(0), diry(0), speed(0), speedgravity(0), speedalpha(0), id(-1), alpha(256), remove(false)
{

}

Particle::Particle(float x,float y,float dirx,float diry,float speed,float speedalpha,int id)
    : x(x), y(y), dirx(dirx), diry(diry), speed(speed), speedgravity(0), speedalpha(speedalpha), id(id), alpha(256), remove(false)
{

}

void Particle::update(float time)
{
    this->x+=this->speed*this->dirx*time;
    this->y+=this->speed*this->diry*time;
    this->y+=this->speedgravity*time;
    this->alpha-=this->speedalpha*time;
}
