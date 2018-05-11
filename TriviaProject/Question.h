#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
	Question(std::string question, std::vector<std::string> possibleAnswers, std::string correctAnswer);
	std::string getQuestion();
	std::vector<std::string> getPossibleAnswers();
	std::string getCorrectAnswer();
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
	std::string m_correctAnswer;
};