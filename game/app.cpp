#include <SFML/Graphics.hpp>
#include <iostream>
#include "app.h"

using namespace sf;
using namespace std;

App::App()
    :w(0), h(0), title("app title"), version("")
{

}

App::App(int w, int h, string title, string version)
    : w(w), h(h), title(title), version(version)
{
    this->window = new RenderWindow(VideoMode(w,h),string(title+" "+version));
}

int App::getW(){
    return w;
}

int App::getH(){
    return h;
}

string App::getTitle(){
    return title;
}

string App::getVersion(){
    return version;
}

RenderWindow* App::getWindow(){
    return window;
}
