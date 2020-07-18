#pragma once
#include <random>
#include "RequestHandlerFactory.h"
#include "Game.h"
class GameManager
{
public:
	GameManager();
	GameManager(IDatabase* database);
	Game createGame(Room* currentRoom);
	void deleteGame(Game* target);
private:
	IDatabase* m_database;
	std::vector<Game> m_games;
	std::vector<Question> generateQuestions(Room* currentRoom);
};

