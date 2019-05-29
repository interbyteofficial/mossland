#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "inventory.h"
#include "camera.h"

#define STATS_HP_DEFAULT 100
#define STATS_HPMAX_DEFAULT 100
#define STATS_HPREGEN_DEFAULT 20

#define STATS_FOOD_DEFAULT 65
#define STATS_FOODMAX_DEFAULT 120
#define STATS_FOODLOST_DEFAULT 22

#define STATS_WATER_DEFAULT 80
#define STATS_WATERMAX_DEFAULT 120
#define STATS_WATERLOST_DEDAULT 16

#define STATS_ENERGY_DEFAULT 100
#define STATS_ENERGYMAX_DEFAULT 300
#define STATS_ENERGYREGENMAX_DEFAULT 100
#define STATS_ENERGYREGEN_DEFAULT 2

#define PLAYER_ANIM_WALK_SPEED_DEFAULT 0.012
#define PLAYER_ANIM_WALK_FRAMES_DEFAULT 7
#define PLAYER_ANIM_WALK_NAME_DEFAULT "anim_playerwalk"

#define PLAYER_SPEED_DEFAULT 0.1
using namespace sf;
using namespace std;

//###
//### Stats | Stats of player
//###
struct Stats
{
    float hp;
    float hpmax;
    float hpregen;

    float food;
    float foodmax;
    float foodlost;

    float water;
    float watermax;
    float waterlost;

    float energy;
    float energymax;
    float energyregen;
    Stats();
};

//###
//### Player
//###
class Player
{
private:
    float x,y,w,h;
    int dirx,diry;
    RectangleShape *rect=NULL;
    Animation *animation=NULL;
    bool ismoving;

    float speed;

    Stats stats;
    //Inventory inventory;
public:
    //### constructors ###
    Player();
    Player(Texture *texture,int x,int y,int w,int h,float speed=PLAYER_SPEED_DEFAULT);

    //### destructors ###
    ~Player();

    //### update ###
    void update(float time);

    //### draw ###
    void draw(RenderWindow *window,Camera *camera);

    //### move ###
    void move(int dirx,int diry);

    //### getters ###
    Stats* getStats();
};

#endif // PLAYER_H_INCLUDED
