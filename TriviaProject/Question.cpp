#include "Question.h"

Question::Question(std::string question, std::string correctAnswer, std::string firstPossibleAnswer, std::string secondPossibleAnswer, std::string thirdPossibleAnswer) : m_question(question), firstAnswer(firstPossibleAnswer), secondAnswer(secondPossibleAnswer), thirdAnswer(thirdPossibleAnswer), m_correctAnswer(correctAnswer)
{
}

std::string Question::getQuestion()
{
	return m_question;
}

std::vector<std::string> Question::getPossibleAnswers()
{
	std::vector<std::string> possibleAnswers;
	possibleAnswers.push_back(firstAnswer);
	possibleAnswers.push_back(secondAnswer);
	possibleAnswers.push_back(thirdAnswer);

	return possibleAnswers;
}

std::string Question::getCorrectAnswer()
{
	return m_correctAnswer;
}
