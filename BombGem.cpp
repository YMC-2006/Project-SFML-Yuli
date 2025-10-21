#include <iostream>
#include "BombGem.h"
#include "Gem.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

Texture BombGem::bombTexture[5];
bool BombGem::bombTextureLoaded = false;

BombGem::BombGem(int type) {
    if (!bombTextureLoaded) {
        bombTexture[0].loadFromFile("assets/gemBombPurple.png");
        bombTexture[1].loadFromFile("assets/gemBombYellow.png");
        bombTexture[2].loadFromFile("assets/gemBombGreen.png");
        bombTexture[3].loadFromFile("assets/gemBombBlue.png");
        bombTexture[4].loadFromFile("assets/gemBombRed.png");
        bombTextureLoaded = true;
       
       
    }
    this->type = type;
    sprite.setTexture(bombTexture[type]);
  
}

BombGem::~BombGem() {

}
