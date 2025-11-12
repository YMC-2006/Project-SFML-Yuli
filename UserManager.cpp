#include <iostream>
#include "UserManager.h"
using namespace std;


UserManager::UserManager(const string& file) : filename(file) {
	loadFromFile();
}


void UserManager::loadFromFile() {
	users.clear();
	ifstream inputFile(filename);
	if (!inputFile.is_open()) {
		cout << "No existing users.json file found. Starting fresh.\n";
		return;
	}


	json data;


	try {
		inputFile >> data;
	}
	catch (const exception& e) {
		cout << "JSON parse error: " << e.what() << endl;
		return;
	}



	for (auto& userData : data) {

		string username = userData["Username"];
		string password = userData.value("Password", "");
		User user(username, password);

		for (auto& lvl : userData["UnlockedLevels"]) {

			int lvlNum = lvl["levelNumber"];
			int score = lvl["score"];

			user.addOrUpdateLevel(lvlNum, score);
		}

		users.push_back(user);
	}



}

void UserManager::saveToFile() {

	json data = json::array();
	
    for (const auto& user : users) {
        json unlocked = json::array();
        for (const auto& lvl : user.getUnlockedLevels()) {
            unlocked.push_back({
                {"levelNumber", lvl.levelNumber},
                {"score", lvl.score}
            });
        }

        data.push_back({
            {"Username", user.getUsername()},
			{"Password", user.getPassword()},
            {"UnlockedLevels", unlocked}
        });
    }

	ofstream out(filename);
	out << data.dump(4);

	cout << "Saving " << users.size() << " users.\n";
	for (const auto& u : users) {
		cout << u.getUsername() << " has "
			<< u.getUnlockedLevels().size()
			<< " levels.\n";
	}

}


void UserManager::addUser(const User& user) {

	users.push_back(user);
	saveToFile();

}

User* UserManager::findUser(const string& username, const string& password) {
	// we are gonna search this->username and this->password to see if the user exist
	for (auto& user : users) {
		if (user.getUsername() == username && user.getPassword() == password) {
			return &user;
		}
	}
	return nullptr;
}

User* UserManager::findUserByName(const string& username) {

	for (auto& user : users) {
		if (user.getUsername() == username) {
			return &user;
		}
	}

	return nullptr;
}

vector<User> UserManager::getUsersSortedByScore() const {

	vector<User> sortedUsers = users;

	sort(sortedUsers.begin(), sortedUsers.end(), [](const User& a, const User& b) {
		return a.getTotalScore() > b.getTotalScore(); // Descending
	});


	return sortedUsers;
	 
}