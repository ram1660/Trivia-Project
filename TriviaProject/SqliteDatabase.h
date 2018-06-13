#pragma once
#include "IDatabase.h"
class SqliteDatabase : public IDatabase
{
public:
public:
	//std::list<Question> getQuestions (int);
	//std::map<LoggedUser, int> getHighscores();
	SqliteDatabase();
	~SqliteDatabase();
	//user
	bool doesUserExists(std::string username) override;
	void createUser(std::string username, std::string password, std::string email) override;
	void deleteUser(LoggedUser& user) override;
	bool DoesPasswordMatchUser(std::string username, std::string password) override;
	static int callbackUser(void * data, int argc, char ** argv, char ** azColName);
	static int doesUserExistsCallback(void * data, int argc, char ** argv, char ** azColName);
	//questions

	bool open() override;
	//void close();
	void clear() override;

private:

	sqlite3 * db;
};

/*
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

#include "Question.h"


class IDatabase
{
public:
//std::list<Question> getQuestions (int);
//std::map<LoggedUser, int> getHighscores();
IDatabase();
~IDatabase();
//user


//questions

bool open();
//void close();
void clear();

private:

sqlite3 * db;
};

*/