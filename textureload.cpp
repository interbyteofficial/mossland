#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "texturebase.h"

using namespace sf;
using namespace std;

TextureBase::Texturebase()
{

}

TextureBase::~TextureBase()
{
    while(this->vector_main.size()>0){
        auto it=vector_main.end();
        vector_main.erase(it);
        delete it;

    }
}
