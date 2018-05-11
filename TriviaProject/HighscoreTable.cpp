#include "HighscoreTable.h"



HighscoreTable::HighscoreTable()
{
}

HighscoreTable::HighscoreTable(IDatabase * db) : m_database(db)
{
}


HighscoreTable::~HighscoreTable()
{
}

std::map<LoggedUser*, int> HighscoreTable::getHighscores()
{
	std::map<LoggedUser*, int> temp;
	return temp;
}
