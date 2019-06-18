#ifndef STATUSBAR_H_INCLUDED
#define STATUSBAR_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#include "camera.h"

using namespace sf;
using namespace std;
class StatusBar
{
protected:
    int x,y;
    float w,h;

    RectangleShape *rectout=NULL;
    RectangleShape *rectin=NULL;
    Color color1,color2,color3;

    float max;
    float value;
    float border;

    bool deleted;
    bool visible;

    int id;
    string name;
public:
    StatusBar();
    StatusBar(string name,int id,int x,int y,int w,int h,float max,float value,Color color1,Color color2,Color color3,int border);
    StatusBar(string name,int id);
    ~StatusBar();

    void setPosition(int x,int y);
    void setSize(float w,float h,float border);
    void setColors(Color colormain,Color colorbg,Color colroborder);
    void setBorder(float border);

    void setValue(float value);
    void setMaxvalue(float maxvalue);

    void setVisible(bool state);
    void setDeleted(bool state);

    //### getters ###
    Vector2f getPosition();
    Vector2f getSize();

    virtual void update(float time);
    virtual void draw(RenderWindow *window,Camera *camera);
};

#endif // STATUSBAR_H_INCLUDED
