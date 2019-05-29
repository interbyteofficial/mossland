#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "app.h"
#include "animation.h"
#include "texturebase.h"
#include "player.h"
#include "particle.h"
#include "camera.h"

using namespace sf;
using namespace std;

int main_menu(App *app)
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
    Animation anim_partemmit_stone("anim_partemmit_stone",1,const_cast<Texture*>(texturebase->getTexture("texturelist_1")),4,0.01);
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

    //
    // Rectangle
    //
    RectangleShape *rect_test=new RectangleShape(Vector2f(64,44));
    rect_test->setPosition(Vector2f(100,100));
    rect_test->setTexture(texturebase->getTexture("texturelist_1"));
    rect_test->setTextureRect(IntRect(animation_tree.getIntRect()));

    RectangleShape *rect_partemmit_stone=new RectangleShape;
    rect_partemmit_stone->setTexture(texturebase->getTexture("texturelist_1"));
    rect_partemmit_stone->setTextureRect(IntRect(0,202,6,6));

    //
    // Particles
    //
    ParticleEmmiter *partemmit_stone=new ParticleEmmiter(100+64/2-12/2,100+12/2-12/2,6,6,rect_partemmit_stone);
    partemmit_stone->createParticles(30,0.05,0.1,0.5,1,PARTICLE_GRAVITY_DEFAULT);
    float timer_partemmit=0;

    //
    // Player
    //
    Player *player=new Player(const_cast<Texture*>(texturebase->getTexture("texturelist_1")),0,0,52,88);

    //
    // Camera
    //
    Camera *camera=new Camera(0,0,CAMERA_SPEED_DEFAULT);

    //
    // Controls
    //
    Vector2i mpos;

    //
    // Main loop
    //
    Clock clock;
    float time=0;
    float gtime=0;
    while(window->isOpen())
    {
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

            if(Mouse::isButtonPressed(Mouse::Button::Left)){
                if(timer_partemmit<=gtime){
                    //cout<<"emmit particle at x:"<<mpos.x<<" y:"<<mpos.y<<endl;
                    //partemmit_stone->clear();
                    anim_partemmit_stone.startAnim();
                    partemmit_stone->setPosition(mpos.x-12/2,mpos.y-12/2);
                    partemmit_stone->createParticles(15,0.05,0.1,0.3,0.6,PARTICLE_DEC_DEFAULT,PARTICLE_GRAVITY_DEFAULT);
                    timer_partemmit=gtime+100;
                }
            }
        }
        //### clear ###
        window->clear(Color(220,220,220));

        //### update ###
        rect_test->setTextureRect(animation_tree.getIntRect());
        animation_tree.update(time);
        anim_player->update(time);
        partemmit_stone->update(time);

        player->update(time);

        //### draw ###
        window->draw(*rect_test);
        partemmit_stone->draw(window);

        player->draw(window,camera);

        //### display ###
        window->display();
    }
    return 0;
}
int main()
{
    App app(1080,720,"pixel world","0.01");
    main_menu(&app);
    return 0;
}
