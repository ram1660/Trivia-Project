#pragma once
#include <map>
#include "IDatabase.h"
class IDatabase;
class LoggedUser;
class HighscoreTable : public IDatabase
{
public:
	HighscoreTable();
	HighscoreTable(IDatabase * db);
	~HighscoreTable();
	std::map<LoggedUser, int> getHighscores() override;
private:
	IDatabase * m_database;
};

