#pragma once
#include "LoggedUser.h"
#include "Question.h"
#include <map>
#include <list>
#include <vector>
class IDatabase
{
public:
	virtual std::map<LoggedUser*, int> getHighscores() = 0;
	virtual bool doesUserExists(std::string username) = 0;
	virtual std::list<Question*> getQuestion(int amount) = 0;
};

