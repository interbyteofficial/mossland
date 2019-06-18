#ifndef TEXTUREBASE_H_INCLUDED
#define TEXTUREBASE_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

using namespace sf;
using namespace std;

Texture* loadTextureFile(string name,string path);

//###
//### TextureBase | class to storage sf::Texture
//###
class TextureBase
{
protected:
    //main vector of claas
    vector<pair<pair<int,string>,Texture*>> vector_main;

public:
    //### constructor ###
    TextureBase();

    //### destructor ###
    ~TextureBase();

    //### load ###
    void loadTexture(string name, string path);

    //### getters
    const Texture* getTexture(string name);
};


#endif // TEXTUREBASE_H_INCLUDED
