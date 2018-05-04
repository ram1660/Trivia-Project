#include "Question.h"

Question::Question(std::string question, std::vector<std::string> possibleAnswers, std::string correctAnswer) : m_question(question), m_possibleAnswers(possibleAnswers), m_correctAnswer(correctAnswer)
{
}

std::string Question::getQuestion()
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	return m_possibleAnswers;
}

std::string Question::getCorrectAnswer()
{
	return m_correctAnswer;
}
