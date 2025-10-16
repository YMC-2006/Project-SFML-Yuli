#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

class Gem {
protected:

	int type; // 0 = purple, 1 = yellow, 2 = green, 3 = blue, 4 = red
	Sprite sprite;
	bool selected = false;


public:

	//Constructor
	Gem();
	~Gem();


	void initGem(int t, Texture& tex); // initialize gem
	virtual int getType();
	void setType(int t);
	Sprite& getSprite();
	void setSprite(Sprite& s);
	bool isSelected();
	void setSelected(bool s);

	
};