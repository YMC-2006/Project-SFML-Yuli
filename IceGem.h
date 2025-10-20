#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gem.h"
using namespace std;
using namespace sf;


class IceGem : public Gem {

private:

	static Texture iceTextures[5]; 
	static bool iceTexturesLoaded;
	bool frozen = true;


public:

	IceGem(int type = 0);
	~IceGem();

};