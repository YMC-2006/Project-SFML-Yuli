#pragma once
#include "LevelConfig.h"
#include "UserManager.h"
#include <iostream>
using namespace std;
using namespace sf;

class Game {
private:

	vector<LevelConfig> levels;
	UserManager userManager;  // loads users.json automatically
	User* currentUser = nullptr;

public:



	Game();
	void userLogin();
	void drawLoginForm();
	void drawRegisterForm();
	void runGame();
	void runLevelsWindow();
	void runSecondWindow(const LevelConfig& config);
	void runThirdWindow(int finalScore, int gemTaskAmount, int levelCompleted);
	

	void updateUnlockedLevels(int completedLevel);
	void setLevels(int index, bool complete);

};
