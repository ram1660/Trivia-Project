#include "Game.h"

Game::Game()
{
}

Game::Game(std::vector<Question> questions) : m_questions(questions)
{
}

Question Game::getQuestionForUser(LoggedUser user)
{
	return Question("asd", "asd", "asd", "zxc", "Asd");
}

bool Game::submitAnswer(unsigned int answer)
{
	return 0;
}

void Game::removePlayer(std::string username)
{
	// for(std::pair<LoggedUser, GameData> loggedUser : m_players)
	// {
	// 	if(loggedUser.first.getUsername() == username)
	// 		m_players.erase(loggedUser.first);
	// }
}
