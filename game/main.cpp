#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <time.h>

#include "app.h"
#include "animation.h"
#include "texturebase.h"
#include "player.h"
#include "particle.h"
#include "camera.h"
#include "obj_static.h"
#include "random.h"
#include "statusbar.h"

using namespace sf;
using namespace std;

int main_game(App *app)
{
    //
    // Window pointer
    //
    RenderWindow *window=app->getWindow();
    window->setFramerateLimit(60);

    //
    // Load data
    //
    TextureBase *texturebase = new TextureBase;
    texturebase->loadTexture("texturelist_1","data/textures/texturelist.png");

    //
    // Init animations
    //

    //animation anim_tree
    Animation animation_tree("anim_tree",0,const_cast<Texture*>(texturebase->getTexture("texturelist_1")),6,0.005);
    animation_tree.setFrameOptions(0,88,32,22);
    animation_tree.setType(ANIM_TYPEREPEAT);

    //animation anim_partemmit_stone
    Animation anim_partemmit_stone("anim_partemmit_stone",1,const_cast<Texture*>(texturebase->getTexture("texturelist_1")),7,0.01);
    anim_partemmit_stone.setFrameOptions(12,202,6,6);
    anim_partemmit_stone.setType(ANIM_TYPEONCE);

    //animation anim_player
    Animation *anim_player=new Animation(PLAYER_ANIM_WALK_NAME_DEFAULT,
                                         2,
                                         const_cast<Texture*>(texturebase->getTexture("texturelist_1")),
                                         PLAYER_ANIM_WALK_FRAMES_DEFAULT,
                                         PLAYER_ANIM_WALK_SPEED_DEFAULT);
    anim_player->setFrameOptions(0,0,26,44);
    anim_player->setType(ANIM_TYPEREPEAT);
    anim_player->startAnim();

    //anim_objr_stone
    Animation anim_objr_stone("anim_objr_stone",
                                         3,
                                         const_cast<Texture*>(texturebase->getTexture("texturelist_1")),
                                         5,
                                         0);
    anim_objr_stone.setFrameOptions(0,88,32,22);
    anim_objr_stone.setType(ANIM_TYPEREPEAT);

    //
    //
    // Rectangle
    //
    RectangleShape rect_partemmit_stone_kick;
    rect_partemmit_stone_kick.setTexture(texturebase->getTexture("texturelist_1"));
    rect_partemmit_stone_kick.setTextureRect(IntRect(0,202,6,6));

    RectangleShape rect_partemmit_stone_destroy;
    rect_partemmit_stone_destroy.setTexture(texturebase->getTexture("texturelist_1"));
    rect_partemmit_stone_destroy.setTextureRect(IntRect(0,191,10,10));


    //
    // Particles
    //
    float timer_partemmit=0;

    ParticleEmmiter partemmit_objr_stone_kick(100+64/2-6/2,100+6/2-6/2,6,6,&rect_partemmit_stone_kick);
    ParticleEmmiter partemmit_objr_stone_destroy(100+64/2-20/2,100+12/2-20/2,20,20,&rect_partemmit_stone_destroy);

    //
    // Object
    //
    ObjectResource asset_objr_stone("stone",0,10,7,const_cast<Texture*>(texturebase->getTexture("texturelist_1")),&anim_objr_stone);
    asset_objr_stone.setParticles(&partemmit_objr_stone_kick,&partemmit_objr_stone_destroy);
    asset_objr_stone.setPosition(100,100);
    asset_objr_stone.setSize(64,44);

    vector<ObjectResource*> vector_objr;
    vector<ObjectStatic*> vector_objs_solid;

    //
    // StatusBar
    //
    StatusBar *statusbar_harvest=new StatusBar("sb_harvest",0,100,100,100,10,12,12,Color(240,50,50),Color(200,200,200),Color(255,255,255),2);
    statusbar_harvest->setVisible(false);

    //
    // Player
    //
    Player *player=new Player(const_cast<Texture*>(texturebase->getTexture("texturelist_1")),app->getW()/2-52/2,app->getH()/2-88/2,52,88);

    //
    // Camera
    //
    Camera *camera=new Camera(0,0,CAMERA_SPEED_DEFAULT);

    //
    // Controls
    //
    Vector2i mpos;

    //
    // Generate World
    //
    //ObjectResource stone
    int option_objrstone_count=1;
    for(int i=0; i<option_objrstone_count; i++)
    {
        //add Stome
        Texture *texture=const_cast<Texture*>(texturebase->getTexture("texturelist_1"));
        ObjectResource* objr_stone=new ObjectResource("obrj_stone",vector_objr.size());

        objr_stone->setStats(12);
        objr_stone->setTexture(const_cast<Texture*>(texturebase->getTexture("texturelist_1")));
        objr_stone->genAnim(6,0,IntRect(0,88,32,22));
        objr_stone->genParticleKick(6,6,IntRect(0,202,6,6));
        objr_stone->genParticleDestroy(30,30,IntRect(0,191,10,10));
        objr_stone->setPosition(random(0,app->getW()-64),random(0,app->getH()-44));
        objr_stone->setSize(64,44);
        vector_objr.push_back(objr_stone);
        vector_objs_solid.push_back(static_cast<ObjectStatic*>(objr_stone));
    }

    //ObjectResource stone
    int option_objrtree_count=1;
    for(int i=0; i<option_objrtree_count; i++)
    {
        //add Stome
        Texture *texture=const_cast<Texture*>(texturebase->getTexture("texturelist_1"));
        ObjectResource* objr_tree=new ObjectResource("obrj_tree",vector_objr.size());

        objr_tree->setStats(12);
        objr_tree->setTexture(const_cast<Texture*>(texturebase->getTexture("texturelist_1")));
        objr_tree->genAnim(4,0,IntRect(0,110,34,40));
        objr_tree->genParticleKick(6,6,IntRect(0,202,6,6));
        objr_tree->genParticleDestroy(30,30,IntRect(0,191,10,10));
        objr_tree->setPosition(random(0,app->getW()-64),random(0,app->getH()-44));
        objr_tree->setSize(136,160);
        vector_objr.push_back(objr_tree);
        vector_objs_solid.push_back(static_cast<ObjectStatic*>(objr_tree));
    }

    //
    // Main loop
    //
    Clock fpsclock;
    Clock clock;
    float time=0;
    float gtime=0;
    float lastframe=0;
    float fps;
    Vertex debugline[2];
    while(window->isOpen())
    {
        float currentframe=fpsclock.restart().asSeconds();
        fps=1.f/abs(currentframe-lastframe);
        lastframe=currentframe;

        time=clock.getElapsedTime().asMicroseconds()/800;
        gtime+=time;
        clock.restart();

        mpos=Mouse::getPosition(*window);

        Event event;
        if(window->pollEvent(event)){
            switch(event.type)
            {
                case Event::Closed:
                    window->close();
                    break;
                default:
                    break;
            }
            int playerdirx=0;
            int playerdiry=0;
            if(Keyboard::isKeyPressed(Keyboard::D)){
                playerdirx=1;
            }
            else if(Keyboard::isKeyPressed(Keyboard::A)){
                playerdirx=-1;
            }
            if(Keyboard::isKeyPressed(Keyboard::S)){
                playerdiry=1;
            }
            else if(Keyboard::isKeyPressed(Keyboard::W)){
                playerdiry=-1;
            }
            player->move(playerdirx,playerdiry);

            bool match=false;
            for(auto it : vector_objr){
                if(it->isMouseover() && it->getHp()>0 && it->getHp()!=it->getMaxhp()){
                    float dx=it->getPosition().x+it->getSize().x/2-player->getPosition().x+player->getSize().x/2;
                    float dy=it->getPosition().y+it->getSize().y/2-player->getPosition().y+player->getSize().y/2;
                    int dist=sqrt((dx*dx)+(dy*dy))-100;
                    if(int(dist)<=PLAYER_HARVEST_DIST){
                        statusbar_harvest->setPosition(it->getPosition().x+it->getSize().x/2-statusbar_harvest->getSize().x/2,it->getPosition().y-statusbar_harvest->getSize().y*2);
                        statusbar_harvest->setVisible(true);
                        statusbar_harvest->setValue(it->getHp());
                        match=true;
                    }
                }
            }
            if(!match){
                statusbar_harvest->setVisible(false);
            }
            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                if(timer_partemmit<=gtime){

                    for(auto it : vector_objr){
                        if(it->isMouseover()){
                            float dx=it->getPosition().x+it->getSize().x/2-player->getPosition().x+player->getSize().x/2;
                            float dy=it->getPosition().y+it->getSize().y/2-player->getPosition().y+player->getSize().y/2;
                            debugline[0]=Vertex(Vector2f(it->getPosition().x+it->getSize().x/2,it->getPosition().y+it->getSize().y/2)),
                            debugline[1]=Vertex(Vector2f(player->getPosition().x+player->getSize().x/2,player->getPosition().y+player->getSize().y/2));
                            int dist=sqrt((dx*dx)+(dy*dy))-100;
                            if(int(dist)<=PLAYER_HARVEST_DIST){
                                (it)->mouseClick(mpos.x,mpos.y,1,camera);
                            }
                        }
                    }
                    timer_partemmit=gtime+200;

                }
            }
        }
        //### clear ###
        window->clear(Color(113,165,84));

        //### update ###

        //camera
        camera->update(time,player->getPosition().x-(app->getW()/2-52/2),player->getPosition().y-(app->getH()/2-88/2));

        //anim
        anim_player->update(time);

        for(int i=0; i<vector_objr.size(); i++){
            auto it=vector_objr.begin()+i;
            if(*it!=NULL){
                (*it)->updateMousepos(mpos.x,mpos.y,camera);
                (*it)->update(time,camera);
            }
            else{
                vector_objr.erase(it);
            }
        }
        cout<<"loop 1\n";

        //deleter for ObjectResource
        for(int i=0; i<vector_objr.size(); i++){
            auto it=vector_objr.begin()+i;
            if(*it!=NULL){
                if((*it)->isDeleted()){
                    delete *it;
                    vector_objr.erase(it);
                    break;
                }
            }
        }
        cout<<"loop 2\n";

        //ObjectStatic(solid)
        for(int i=0; i<vector_objs_solid.size(); i++){
            auto it=vector_objs_solid.begin()+i;
            if(*it==NULL){
                vector_objs_solid.erase(it);
                break;
            }
        }
        cout<<"loop 3\n";

        //player
        player->update(time,vector_objs_solid,camera);

        //gui
        statusbar_harvest->update(time);

        //debug
        //cout<<"FPS: "<<int(fps)<<endl;

        //############
        //### draw ###
        //############
        //window->draw(*rect_test);
        for(auto it : vector_objr){
            if(it!=NULL)
                (it)->draw(window,camera);
        }

        //player
        player->draw(window,camera);

        //gui
        statusbar_harvest->draw(window,camera);

        //debug
        //window->draw(debugline,2,Lines);
        //### display ###
        window->display();
    }
    return 0;
}
int main()
{
    srand(time(NULL));
    App app(1080,720,"pixel world","0.01");
    main_game(&app);
    return 0;
}
