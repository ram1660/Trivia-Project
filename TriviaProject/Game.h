#pragma once
#include "structures.h"
#include "LoggedUser.h"
class LoggedUser;
class Game
{
public:
	Game();
	Game(std::vector<Question> questions);
	Question getQuestionForUser(LoggedUser user);
	bool submitAnswer(unsigned int answer);
	void removePlayer(std::string username);
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser, GameData> m_players;
};

