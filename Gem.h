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

	bool isMoving = false;
	Vector2f startPos;
	Vector2f endPos;
	float progress = 0.f; // entre 0.0 y 1.0
	float speed = 5.f;    



public:

	//Constructor
	Gem();

	void initGem(int t, Texture& tex); // initialize gem
	int getType();
	void setType(int t);
	Sprite& getSprite();
	bool isSelected();
	void setSelected(bool s);



	
	

	
};