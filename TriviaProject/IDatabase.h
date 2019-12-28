#pragma once
#include <iostream>
#include <winsock2.h>
#include <map>
#include <string>
#include <list>
#include <io.h>

#include "LoggedUser.h"
#include "sqlite3.h"

#include "Question.h"


class IDatabase
{
public:
	//std::list<Question> getQuestions (int);
	//std::map<LoggedUser, int> getHighscores();
	
	//user
	virtual bool doesUserExists(std::string username) = 0;
	virtual void createUser(std::string username, std::string password, std::string email) = 0;
	virtual void deleteUser(LoggedUser& user) = 0;
	virtual bool DoesPasswordMatchUser(std::string username, std::string password) = 0;

	//questions

	virtual bool open() = 0;
	virtual void clear() = 0;


};

