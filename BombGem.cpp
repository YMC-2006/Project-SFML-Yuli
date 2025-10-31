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

    //had to add this here bc we are initializing the sprite and without it the gem wont have the right scale or position
    sprite.setOrigin(
        sprite.getTexture()->getSize().x / 2.f,
        sprite.getTexture()->getSize().y / 2.f
    );
    sprite.setScale(.70f, .70f); //the size of each individual gem is 70px cus 80 to big
}



BombGem::~BombGem() {

}
