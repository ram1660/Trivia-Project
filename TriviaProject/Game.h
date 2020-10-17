#pragma once
#include "structures.h"
#include "LoggedUser.h"
#include "Timer.h"
class Game
{
public:
	Game();
	~Game();
	Game(std::vector<Question> questions);
	Question& getQuestionForUser(LoggedUser& user);
	unsigned int submitAnswer(unsigned int answer, LoggedUser& answeringPlayer) noexcept;
	void removePlayer(const std::string username);
	std::map<LoggedUser*, GameData> getPlayers() const;
	std::map<LoggedUser*, Timer*> getAnsweringTimers();
private:
	std::vector<Question> m_questions;
	std::map<LoggedUser*, GameData> m_players;
	std::map<LoggedUser*, Timer*> m_players_timer;
};

