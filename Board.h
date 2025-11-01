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
	bool isUnlocked;
	
	bool boosterActive = false; // booster is used
	bool boosterUnlocked = false; // comes from level Config

	//Bar progress
	
	int currentProgressPoints;
	int targetProgressPoints;
	float maxWidth;
	int barPoints;
	RectangleShape outline;
	RectangleShape fill;
	bool thereIsTaskMatch = false;
	
	
	

public:

	Board(const LevelConfig& config);
	void drawScene(RenderWindow& window, Event& event);
	
	int noInitialMatch(int i, int j);
	void fillMatrix();
	void drawBoard(RenderWindow &gameWindow);
	void activateBooster();
	void swapGems(RenderWindow& gameWindow, Event& event);
	//void generateBombGems(int x1, int y1, int x2, int y2, int matchedGems, bool enableBombGems, bool m1, bool m2, int type1, int type2);
	bool checkMatchAt(int x, int y);
	void animateSwap(Gem& g1, Gem& g2, Vector2f targetPos1, Vector2f targetPos2, RenderWindow& window);
	bool deleteMatch(RenderWindow& window);
	bool deleteRowOrColumns(RenderWindow& window);
	int countPoints();
	
	
	void startShake(RenderWindow& window, Gem& g1, Gem& g2, Vector2f pos1, Vector2f pos2); // kinda working but currently out of use
	void pullGravity();
	void animateGravity(RenderWindow& window);
	void floatingTexts(RenderWindow& window, int matchedGems);
	void drawText(RenderWindow& window);

	


	void initBar(); // Inicializes the bar we call this function only once
	void updateGemTaskProgress(int gemsMatchedOfTask); // sets the thereIsProgress variable
	int countGemTaskMatches();
	void barProgress(RenderWindow& window, Event& event,bool thereIsTaskMatch); // Updates and draws the bar progress
	bool progress(); void setProgress(bool p); // sets and gets
	

	int getPoints(); int getMoves(); int getGemTask(); int getGemTaskAmount();
	void setPoints(int p); void setMoves(int m); void setTask(int gems);

	
};