#pragma once
#include <iostream>
#include <vector>
class Question
{
public:
	Question(std::string question, std::string correctAnswer, std::string firstPossibleAnswer, std::string secondPossibleAnswer, std::string thirdPossibleAnswer);
	std::string getQuestion() const;
	std::vector<std::string> getPossibleAnswers();
	std::string getCorrectAnswer() const;
private:
	std::string m_question;
	std::string firstAnswer;
	std::string secondAnswer;
	std::string thirdAnswer;
	std::string m_correctAnswer;
};