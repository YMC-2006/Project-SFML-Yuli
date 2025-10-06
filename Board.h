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

	//Levels mainly
	int pointsCounter = 0;
	int totalMoves = 0;
	int targetScore = 0;
	int levelNumber;
	bool hasIceBlocks;
	bool enableBombGems;

	//Bar progress
	int presses;
	int maxPresses;
	float maxWidth;
	RectangleShape outline;
	RectangleShape fill;
	bool thereIsProgress = false;
	
	
	

public:

	Board(const LevelConfig& config);
	Board();
	
	int noInitialMatch(int i, int j);
	void fillMatrix();
	void drawBoard(RenderWindow &gameWindow);
	bool checkMatchAt(int x, int y);
	void swapGems(RenderWindow& gameWindow, Event& event);
	void animateSwap(Gem& g1, Gem& g2, Vector2f targetPos1, Vector2f targetPos2, RenderWindow& window);
	void generateBombGem(Gem& g1, int typeGem, Vector2f pos, Texture& tex);
	bool deleteMatch();
	int countPoints();
	
	void startShake(RenderWindow& window, Gem& g1, Gem& g2, Vector2f pos1, Vector2f pos2); // it doesnt work yet :''v
	void pullGravity();
	void animateGravity(RenderWindow& window);
	
	void drawText(RenderWindow& window);


	void initBar(); // Inicialices the bar we call this function only once
	void barProgress(RenderWindow& window, Event& event,bool thereIsMatch); // Actualiza/dibuja
	bool progress(); void setProgress(bool p);

	//void deleteGem(RenderWindow& window, Event& event);
	int getPoints(); int getMoves();
	void setPoints(int p); void setMoves(int m);

	
};