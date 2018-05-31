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

std::map<LoggedUser, int> HighscoreTable::getHighscores()
{
	std::map<LoggedUser, int> highscoresTable;
	// Quries to the db asking for the highscore table most likely it will return a map with loggedUser object and the score.
	return highscoresTable;
}
