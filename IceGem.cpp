#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Board.h"
#include "IceGem.h"
#include <SFML/Audio.hpp>
#include <ctime>
using namespace std;
using namespace sf;


IceGem::IceGem() {
    textures[0].loadFromFile("assets/purpleIceGem.png");
    textures[1].loadFromFile("assets/yellowIceGem.png");
    textures[2].loadFromFile("assets/greenIceGem.png");
    textures[3].loadFromFile("assets/blueIceGem.png");
    textures[4].loadFromFile("assets/redIceGem.png");
    initGem(0, textures[0]);
}



IceGem::~IceGem() {

}