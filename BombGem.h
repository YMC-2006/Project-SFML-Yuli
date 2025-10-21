#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Gem.h"
using namespace std;
using namespace sf;

class BombGem: public Gem {

private:

	static Texture bombTexture[5];
	static bool bombTextureLoaded;


public:
	BombGem(int type = 0);
	~BombGem();

	int getPointsValue() const override { return 15; }  // 💥 POLIMORPHISM
	
};
