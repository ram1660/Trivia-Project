#include "GameManager.h"

GameManager::GameManager(IDatabase* database) : m_database(database)
{
}

Game* GameManager::createGame(Room* currentRoom)
{
	Game* newGame = new Game(generateQuestions(currentRoom));
	for (LoggedUser* user : currentRoom->getAllUsers())
	{
		Timer* newTimer = new Timer();
		newGame->getAnsweringTimers().emplace(std::make_pair(user, newTimer));
	}
	m_games.push_back(newGame);
	return newGame;
}

void GameManager::deleteGame(Game* target)
{
	for (size_t i = 0; i < m_games.size(); i++)
		if(m_games[i] == target)
			m_games.erase(m_games.begin() + i);
}

std::vector<PlayerResults> GameManager::getPlayersResults()
{
	std::vector<PlayerResults> results;
	for (auto game : m_games)
	{
		//for(auto user : game->getPlayers())
		//	user.second.
	}
	return std::vector<PlayerResults>();
}

std::vector<Question> GameManager::generateQuestions(Room* currentRoom)
{
	std::vector<Question> collection;
	collection = m_database->generateRandomQuestions();
	return collection;
}
