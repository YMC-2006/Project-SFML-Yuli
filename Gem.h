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
	static Texture textures[5];
	static bool texturesLoaded;

public:

	//Constructor
	Gem();
	~Gem();

	virtual void initGem(int t); // initialize gem
	virtual int getPointsValue() const { return 10; }  // 🔹 Puntos base
	virtual int getType();
	void setType(int t);
	Sprite& getSprite();
	void setSprite(Sprite& s);
	static const Texture& getTexture(int index);
	virtual bool isSelected();
	void setSelected(bool s);
	

	// ⚡ Load the textures
	static void loadTextures();
};