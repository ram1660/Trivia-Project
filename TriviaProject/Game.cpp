#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
	for (auto &timer : m_players_timer)
		delete timer.second;

}

Game::Game(std::vector<Question> questions) : m_questions(questions)
{
}

Question& Game::getQuestionForUser(LoggedUser& user)
{
	Timer* newTimer = new Timer();
	m_players_timer.emplace(std::make_pair(&user, newTimer));
	m_players_timer.at(&user)->start();
	return *m_players.find(&user)->second.currentQuestion;
}

unsigned int Game::submitAnswer(unsigned int answer, LoggedUser& answeringPlayer) noexcept
{
	unsigned int correctAnswerIndex = 0;
	const std::vector<std::string> answers = m_players[&answeringPlayer].currentQuestion->getPossibleAnswers();
	for (size_t i = 0; i < m_questions.size(); i++)
	{
		if (!m_players.at(&answeringPlayer).currentQuestion->getCorrectAnswer().compare(answers[i]))
			break;
		correctAnswerIndex++;
	}
	m_players_timer.at(&answeringPlayer)->stop();
	m_players.at(&answeringPlayer).currentQuestionIndex++;
	m_players.at(&answeringPlayer).currentQuestion = &m_questions[m_players.at(&answeringPlayer).currentQuestionIndex];
	if (answer == correctAnswerIndex)
	{
		m_players.at(&answeringPlayer).correctAnswerCount++;
		return answer;
	}
	else
	{
		m_players.at(&answeringPlayer).wrongAnswerCount++;
		return correctAnswerIndex;
	}
}

void Game::removePlayer(const std::string username)
{
	for (auto &player : m_players)
		if (player.first->getUsername() == username)
			m_players.erase(player.first);
}

std::map<LoggedUser*, GameData> Game::getPlayers() const
{
	return m_players;
}

std::map<LoggedUser*, Timer*> Game::getAnsweringTimers()
{
	return m_players_timer;
}

