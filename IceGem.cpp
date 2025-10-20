#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Board.h"
#include "IceGem.h"
#include <SFML/Audio.hpp>
#include <ctime>
using namespace std;
using namespace sf;

Texture IceGem::iceTextures[5];
bool IceGem::iceTexturesLoaded = false;


IceGem::IceGem(int type) {

	if (!iceTexturesLoaded) {
		iceTextures[0].loadFromFile("assets/purpleIceGem.png");
		iceTextures[1].loadFromFile("assets/yellowIceGem.png");
		iceTextures[2].loadFromFile("assets/greenIceGem.png");
		iceTextures[3].loadFromFile("assets/blueIceGem.png");
		iceTextures[4].loadFromFile("assets/redIceGem.png");
		iceTexturesLoaded = true;
		
	}
   
	this->type = type;
	sprite.setTexture(iceTextures[type]);

}



IceGem::~IceGem() {

}