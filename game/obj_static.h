#ifndef OBJ_STATIC_H_INCLUDED
#define OBJ_STATIC_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <math.h>
#include <iostream>

#include "animation.h"
#include "camera.h"
#include "particle.h"

#define OBJSTATIC_RESOURCESTONE_HP 10

using namespace std;
using namespace sf;

inline bool collideRect(int x,int y,int w,int h,int mx,int my);
bool collideRectIn(int x,int y,int w,int h,int mx,int my);

class ObjectStatic
{
protected:
    float x,y;
    float w,h;
    RectangleShape *rect=NULL;
    Animation *anim=NULL;
    Texture *texture=NULL;

    bool solid;
    bool visible;
    bool mouseover;
    bool deleted;

    string name;
    int id;
public:
    ObjectStatic();
    ObjectStatic(string name,int id);
    ObjectStatic(float x,float y,float w,float h,Texture *texture,Animation *anim,string name,int id=-1);

    void setPosition(float x,float y);
    void setSize(float w,float h);
    void setSolid(bool state);
    void setVisible(bool state);
    void setDeleted(bool state);

    bool isSolid();
    bool isVisible();
    bool isMouseover();
    bool isDeleted();

    virtual void draw(RenderWindow *window,Camera *camera);
    virtual void update(float time);
    virtual void updateMousepos(int mx,int my,Camera *camera);

    Vector2f getSize();
    Vector2f getPosition();
};

class ObjectResource : public ObjectStatic
{
protected:
    float hp;
    float maxhp;
    int maxframe;

    RectangleShape *rect=NULL;
    Animation *anim=NULL;
    ParticleEmmiter *prtemm_kick=NULL;
    ParticleEmmiter *prtemm_destroy=NULL;

    RectangleShape *rect_prtemm_kick=NULL;
    RectangleShape *rect_prtemm_destroy=NULL;

    bool destroyed;

public:
    ObjectResource();
    ObjectResource(string name,int id);
    ObjectResource(string name,int id,int hp,int maxframe,Texture *texture,Animation *anim);
    ~ObjectResource();

    void setTexture(Texture *texture);
    void genAnim(int maxframe,float speed,IntRect intrect,Texture *texture=NULL);
    void genParticleKick(int w,int h,IntRect intrect,Texture *texture=NULL);
    void genParticleDestroy(int w,int h,IntRect intrect,Texture *texture=NULL);

    void setStats(int hp);
    void setPosition(float x,float y);
    void setSize(float w,float h);
    void setParticles(ParticleEmmiter *prtemm_kick,ParticleEmmiter *prtemm_destroy);
    void mouseClick(int mx,int my,float power,Camera *camera);

    float getHp();
    float getMaxhp();

    void draw(RenderWindow *window,Camera *camera);
    void update(float time,Camera *camera);
};
#endif // OBJ_STATIC_H_INCLUDED
