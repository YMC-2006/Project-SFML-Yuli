#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
using namespace std;

struct LevelScore {
	int levelNumber;
	int score;
};


class User {
private:

	string username;
	string password;
	vector<LevelScore> unlockedLevels; // each with a score
	

	

public:

	User(const string& username, const string& password)
	: username(username), password(password) { }

	string getUsername() const { return username; }
	string getPassword() const { return password; }
	const vector<LevelScore>& getUnlockedLevels() const { return unlockedLevels; }


	void addOrUpdateLevel(int levelNumber, int score);
	int getTotalScore() const ; // for the leaderboard ;)

};