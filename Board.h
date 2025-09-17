#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gem.h"
using namespace std;
using namespace sf;

class Board {
private:
	bool firstClick = false;
	int x1, y1; // coords of the first click
	static const int size = 8;
	Gem matrix[size][size];
	Texture textures[5];
	Gem* selectedGem = nullptr;
	int pointsCounter = 0;
	int totalMoves = 20;

	


public:

	Board();
	void fillMatrix();
	void drawBoard(RenderWindow &gameWindow);
	void swapGems(RenderWindow& gameWindow, Event& event);
	bool checkMatchAt(int x, int y);
	int countPoints();
	bool deleteMatch();
	void startShake(RenderWindow& window, Gem& g1, Gem& g2, Vector2f pos1, Vector2f pos2); // it doesnt work yet :''v
	void pullGravity();
	int noInitialMatch(int i, int j);
	void drawText(RenderWindow& window, Event& event);

	
	//void deleteGem(RenderWindow& window, Event& event);
	int getPoints(); int getMoves();
	void setPoints(int p); void setMoves(int m);
};