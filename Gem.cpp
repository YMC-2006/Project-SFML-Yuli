#include <SFML/Graphics.hpp>
#include "Gem.h"
#include "Board.h"
#include <cstdlib> // rand
using namespace sf;
using namespace std;

Gem::Gem() {

   
}

Gem::~Gem() {

}   


void Gem::initGem(int t, Texture& tex) {
    type = t;
    sprite.setTexture(tex);
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

    
bool Gem::isSelected() {
    return selected;
}
void Gem::setSelected(bool s) {
    selected = s;

}

void Gem::setType(int t) {
    type = t;

}


