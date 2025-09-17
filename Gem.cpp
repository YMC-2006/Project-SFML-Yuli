#include <SFML/Graphics.hpp>
#include "Gem.h"
#include <cstdlib> // para rand
using namespace sf;
using namespace std;

Gem::Gem() {
    type = 0;
}


void Gem::initMatrix(int t, Texture& tex) {
    type = t;
    sprite.setTexture(tex);
    sprite.setScale(.70f, .70f); //the size of each individual gem is 70px cus 80 to big

}

void Gem::startShake() {

}


int Gem::getType(){
    return type;
}

Sprite& Gem::getSprite() {
    return sprite;
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




