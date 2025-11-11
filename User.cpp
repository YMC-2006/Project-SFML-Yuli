#include <iostream>
#include "User.h"
#include <SFML/Graphics.hpp>
using namespace std;


void User::addOrUpdateLevel(int levelNumber, int score) {

	for (auto& level : unlockedLevels) {
		if (level.levelNumber == levelNumber) {
			level.score = score;
			cout << "Updated existing level " << levelNumber << " score " << score << "\n";

			return;
		}
		else {
			cout << "Added new level " << levelNumber << " score " << score << "\n";
			unlockedLevels.push_back({ levelNumber, score });

		}
	}


}


int User::getTotalScore() const {

	int totalScore = 0;

	for (const auto& level : unlockedLevels) {
		totalScore += level.score;
		
	}

	return totalScore;
}