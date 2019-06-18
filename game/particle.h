#ifndef PARTICLE_H_INCLUDED
#define PARTICLE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "camera.h"

#define PARTICLE_DEC_DEFAULT 0.00002
#define PARTICLE_GRAVITY_DEFAULT 0.0002

using namespace sf;
using namespace std;

struct Particle;

class ParticleEmmiter
{
private:
    int x,y;
    int w,h;
    float angle;
    float gravityspeed;
    float decspeed;

    RectangleShape *rect=NULL;
    vector<Particle*> vector_particles;

public:
    //### constructor ###
    ParticleEmmiter(int x,int y,int w,int h,RectangleShape *rect);
    ParticleEmmiter();

    //### destructor ###
    ~ParticleEmmiter();

    //### update ###
    void update(float time);

    //### draw ###
    void draw(RenderWindow *window,Camera *camera);

    //### main func ###
    void clear();
    void createParticles(int num,float speed,float speedmax,float alphaspeed=0,float alphaspeedmax=0,float decspeed=0,float gravityspeed=0);

    //### setters ###
    void setPosition(int x,int y);
    void addPosition(int x,int y);
    void setRect(RectangleShape *rect);

    //### getters ###
    int getCount();
};
struct Particle
{
    float x,y;
    float dirx,diry;
    float speed;
    float speedgravity;
    float speedalpha;
    float alpha;
    int id;

    bool remove;

    Particle();
    Particle(float x,float y,float dirx,float diry,float speed,float speedalpha,int id);
    void update(float time);
};

#endif // PARTICLE_H_INCLUDED
