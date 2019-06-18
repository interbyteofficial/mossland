#ifndef APP_H_INCLUDED
#define APP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class App
{
    int w,h;
    string title;
    string version;
    RenderWindow *window=NULL;

public:
    App();
    App(int,int,string,string);
    int getW();
    int getH();
    string getTitle();
    string getVersion();
    RenderWindow* getWindow();
};


#endif // APP_H_INCLUDED
