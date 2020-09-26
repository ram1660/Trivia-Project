#pragma once
#include <random>
#include "Room.h"
#include "IDatabase.h"
#include "Game.h"
class GameManager
{
public:
	GameManager(IDatabase* database);
	Game* createGame(Room* currentRoom);
	void deleteGame(Game* target);
	std::vector<PlayerResults> getPlayersResults();
private:
	IDatabase* m_database;
	std::vector<Game*> m_games;
	std::vector<Question> generateQuestions(Room* currentRoom);
};