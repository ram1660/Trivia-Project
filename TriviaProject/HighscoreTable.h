#pragma once
#include "IDatabase.h"
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

