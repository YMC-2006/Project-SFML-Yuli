#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Gem.h"
#include "LevelConfig.h"
using namespace std;
using namespace sf;

class Board {
private:
	bool firstClick = false;
	int x1, y1; // coords of the first click
	static const int size = 8;
	Gem* matrix[size][size];
	Texture textures[5];
	Gem* selectedGem = nullptr;
	

	//Levels
	int pointsCounter = 0;
	int totalMoves = 0;
	int targetScore = 0;
	int levelNumber;
	int gemTask = 0;
	int gemTaskAmount = 0;
	
	
	
	bool hasIceBlocks;
	bool enableBombGems;

	//Bar progress
	
	int currentProgressPoints;
	int targetProgressPoints;
	float maxWidth;
	int barPoints;
	RectangleShape outline;
	RectangleShape fill;
	bool thereIsProgress = false;
	
	
	

public:

	Board(const LevelConfig& config);
	void drawScene(RenderWindow& window, Event& event);
	
	int noInitialMatch(int i, int j);
	void fillMatrix();
	void drawBoard(RenderWindow &gameWindow);
	bool checkMatchAt(int x, int y);
	void swapGems(RenderWindow& gameWindow, Event& event);
	void animateSwap(Gem& g1, Gem& g2, Vector2f targetPos1, Vector2f targetPos2, RenderWindow& window);
	void generateBombGem(Gem& g1, int typeGem, Vector2f pos, Texture& tex);
	void generateIceGems();
	bool deleteMatch();
	int countPoints();
	
	
	void startShake(RenderWindow& window, Gem& g1, Gem& g2, Vector2f pos1, Vector2f pos2); // kinda working but currently out of use
	void pullGravity();
	void animateGravity(RenderWindow& window);
	void floatingTexts(RenderWindow& window, int matchedGems);
	void drawText(RenderWindow& window);

	


	void initBar(); // Inicialices the bar we call this function only once
	void updateGemTaskProgress(); // sets the thereIsMatch variable
	void barProgress(RenderWindow& window, Event& event,bool thereIsMatch); // Updates and draws the bar progress
	bool progress(); void setProgress(bool p); // sets and gets
	

	int getPoints(); int getMoves(); int getGemTask(); int getGemTaskAmount();
	void setPoints(int p); void setMoves(int m); void setTask(int gems);

	
};