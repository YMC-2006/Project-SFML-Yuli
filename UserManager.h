#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"
#include <fstream>
#include "User.h"
using namespace std;

using json = nlohmann::json;


class UserManager {

private:
	
	vector<User> users;
	string filename; // the file that we are gonna readddd period


public:


	UserManager(const string& file = "users.json");

	void loadFromFile();
	void saveToFile();

	void addUser(const User& user);
	User* findUser(const string& username, const string& password);
	User* findUserByName(const string& username);
	const vector<User> getAllUsers() const { return users;  }

};