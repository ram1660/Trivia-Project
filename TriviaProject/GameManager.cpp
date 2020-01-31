#include "GameManager.h"

GameManager::GameManager(IDatabase* database) : m_database(database)
{
}

Game GameManager::createGame(Room* currentRoom)
{

	
	std::vector<Question> questionCollection = generateQuestions(currentRoom);
	return Game();
}

void GameManager::deleteGame(Game* target)
{
	for (size_t i = 0; i < m_games.size(); i++)
		if(&m_games[i] == target)
			m_games.erase(m_games.begin() + i);
}

std::vector<Question> GameManager::generateQuestions(Room* currentRoom)
{
	std::vector<int> chosenNumbers;
	std::vector<Question> collection;
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1, currentRoom->getMetaRoom()->questionCount);
	auto reroll = std::bind(distribution, generator);
	//m_database->getDatabase()
	//return std::vector<Question>();
}
