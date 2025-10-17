#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gem.h"
using namespace std;
using namespace sf;


class IceGem : public Gem {

private:

	Sprite sprite;
	Texture textures[5];

public:

	IceGem();
	~IceGem();

};