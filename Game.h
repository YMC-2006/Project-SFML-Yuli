#pragma once
#include "LevelConfig.h"
#include <iostream>
using namespace std;
using namespace sf;

class Game {
private:

	LevelConfig lastLevel { 1, 20, 1000, 10, false, false };
	

public:

	void runMainWindow();
	void runSecondWindow(const LevelConfig& config);
	void runThirdWindow(int finalScore);
	void runLVLwindow();

};
