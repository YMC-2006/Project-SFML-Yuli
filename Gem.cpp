#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "Board.h"
#include <cstdlib> // rand
using namespace sf;
using namespace std;

Texture Gem::textures[5];
bool Gem::texturesLoaded = false;

Gem::Gem() {
    if (!texturesLoaded) loadTextures();
}

Gem::~Gem() {

}   

void Gem::loadTextures() {
    textures[0].loadFromFile("assets/purpleGem.png");
    textures[1].loadFromFile("assets/yellowGem.png");
    textures[2].loadFromFile("assets/greenGem.png");
    textures[3].loadFromFile("assets/blueGem.png");
    textures[4].loadFromFile("assets/redGem.png");

    texturesLoaded = true;
    cout << "Gem textures loaded successfully.\n";
}


void Gem::initGem(int t) {
    type = t;
    if (t >= 0 && t < 5) {
        sprite.setTexture(textures[t]);
    }
    sprite.setScale(.70f, .70f); //the size of each individual gem is 70px cus 80 to big

}



int Gem::getType(){
    return type;
}

Sprite& Gem::getSprite() {
    return sprite;
 }

void Gem::setSprite(Sprite& s) {
    sprite = s;
}

const Texture& Gem::getTexture(int index) {
    if (index < 0 || index >= 5) {
        static Texture empty;
        return empty; // ERROR HANDLING
    }
    return textures[index];
}
    
bool Gem::isSelected() {
    return selected;
}
void Gem::setSelected(bool s) {
    selected = s;

}

void Gem::setType(int t) {
    type = t;

}


