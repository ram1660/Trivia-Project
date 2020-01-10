#include "HighscoreTable.h"



HighscoreTable::HighscoreTable() : m_database(nullptr)
{
}

HighscoreTable::HighscoreTable(IDatabase * db) : m_database(db)
{
}


HighscoreTable::~HighscoreTable()
{
}

std::map<std::string, unsigned int> HighscoreTable::getHighscores()
{
	std::map<std::string, unsigned int> highscoresTable;
	// Quries to the db asking for the highscore table most likely it will return a map with loggedUser object and the score.
	char* errMessage = nullptr;
	const char* query = "SELECT * FROM HIGHSCORES ORDER BY SCORE";
	int result = sqlite3_exec(m_database->getDatabase(), query, callbackHighscores, &highscoresTable, &errMessage);
	return highscoresTable;
}

// Unsafe needs testing
int HighscoreTable::callbackHighscores(void* data, int argc, char** argv, char** azColName)
{
	std::map <std::string, unsigned int>* highscores{};
	std::string username;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(azColName[i], "USER"))
			username = argv[i];
		else if (!strcmp(azColName[i], "SCORE"))
			highscores->insert(std::pair<std::string, unsigned int>(username, std::atoi(argv[i])));
	}

	data = highscores;
	
	return 0;
}
