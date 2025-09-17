#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Gem {
private:

	int type; // 0 = purple, 1 = yellow, 2 = green, 3 = blue, 4 = red
	Sprite sprite;
	bool moving = false;
	bool selected = false;

public:

	//Constructor
	Gem();

	void initMatrix(int t, Texture& tex); // inicializa gema
	void startShake();
	int getType();
	void setType(int t);
	Sprite& getSprite();
	bool isSelected();
	void setSelected(bool s);


	
	

	
};