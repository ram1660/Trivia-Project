#include "Game.h"

Game::Game()
{
}

Game::Game(std::vector<Question> questions) : m_questions(questions)
{
}

Question Game::getQuestionForUser(LoggedUser user)
{
	return Question();
}

bool Game::submitAnswer(unsigned int answer)
{
	return 0;
}

void Game::removePlayer(std::string username)
{
	m_players.erase(LoggedUser(username));
}
