#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
	Question();
	Question(std::string question, std::string correctAnswer, std::string firstPossibleAnswer, std::string secondPossibleAnswer, std::string thirdPossibleAnswer);
	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers() const;
	std::string getCorrectAnswer() const;
private:
	std::vector<std::string> m_possibleAnswers;
	std::string m_question;
	std::string m_correctAnswer;
};