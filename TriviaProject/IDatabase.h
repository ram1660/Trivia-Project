#pragma once
#include <iostream>
#include <winsock2.h>
#include <map>
#include <string>
#include <list>
#include <io.h>
#include <stdlib.h>
#include "LoggedUser.h"
#include "sqlite3.h"
//#include "User.h"
#include "Question.h"


class IDatabase
{
public:
	//std::list<Question> getQuestions (int);
	//std::map<LoggedUser, int> getHighscores();
	IDatabase();
	~IDatabase();
	//user
	bool doesUserExists(std::string username);
	void createUser(std::string username, std::string password, std::string email);
	void deleteUser(LoggedUser& user);
	bool DoesPasswordMatchUser(std::string username, std::string password);

	//questions

	bool open();
	//void close();
	void clear();

private:

	sqlite3 * db;
};

