#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "texturebase.h"

using namespace sf;
using namespace std;

Texture* loadTextureFile(string name,string path)
{
    Texture *texture=new Texture;
    texture->loadFromFile(path);
    return texture;
}

//###
//### TextureBase
//###
TextureBase::TextureBase()
{

}

TextureBase::~TextureBase()
{
    while(this->vector_main.size()>0){
        auto it=vector_main.end();
        vector_main.erase(it);
        delete it->second;

    }
}

void TextureBase::loadTexture(string name, string path)
{
    Texture *texture=loadTextureFile(name,path);

    pair<pair<int,string>,Texture*> texturepair;
    texturepair.first.first=this->vector_main.size();
    texturepair.first.second=name;
    texturepair.second=texture;

    this->vector_main.push_back(texturepair);
}

const Texture* TextureBase::getTexture(string name)
{
    for(auto it=vector_main.begin(); it!=vector_main.end(); it++){
        if(it->first.second==name)
            return const_cast<const Texture*>(it->second);
    }
}
