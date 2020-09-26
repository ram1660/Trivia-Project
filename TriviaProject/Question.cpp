#include "Question.h"

Question::Question()
{
}

Question::Question(std::string question, std::string correctAnswer, std::string firstPossibleAnswer, std::string secondPossibleAnswer, std::string thirdPossibleAnswer) : m_question(question), m_correctAnswer(correctAnswer)
{
	m_possibleAnswers.push_back(firstPossibleAnswer);
	m_possibleAnswers.push_back(secondPossibleAnswer);
	m_possibleAnswers.push_back(thirdPossibleAnswer);
}

std::string Question::getQuestion() const
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers() const
{
	return m_possibleAnswers;
}

std::string Question::getCorrectAnswer() const
{
	return m_correctAnswer;
}
