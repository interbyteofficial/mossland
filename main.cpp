#include <SFML/Graphics.hpp>
#include <iostream>
#include "app.h"
#include "animation.h"

using namespace sf;
using namespace std;

int main_menu(App *app)
{
    RenderWindow *window=app->getWindow();

    while(window->isOpen())
    {
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
        }
        window->clear(Color(220,220,220));

        window->display();
    }
}
int main()
{
    App app(1080,720,"pixel world","0.01");
    main_menu(&app);
    return 0;
}
