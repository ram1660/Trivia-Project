#pragma once
#include "SqliteDatabase.h"
class IDatabase;
class LoggedUser;
class HighscoreTable
{
public:
	HighscoreTable();
	HighscoreTable(IDatabase * db);
	~HighscoreTable();
	std::map<std::string, unsigned int> getHighscores();


private:
	static int callbackHighscores(void* data, int argc, char** argv, char** azColName);
	IDatabase * m_database;
};

