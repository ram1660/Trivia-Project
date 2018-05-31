#pragma once
#include <iostream>
#include <winsock2.h>
#include <map>
#include <string>
#include <list>
#include "sqlite3.h"
#include <stdlib.h>
#include <io.h>
#include "User.h"
#include "loggedUser.h"
#include "Question.h"


class IDataBase
{
public:
	//std::list<Question> getQuestions (int);
	//std::map<LoggedUser, int> getHighscores();

	//user
	bool doesUserExists(std::string username);
	void createUser(User& user);
	void deleteUser(LoggedUser& user);
	bool DoesPasswordMatchUser(std::string username, std::string password);

	//questions

	bool open();
	//void close();
	void clear();

private:

	sqlite3 * db;
};

