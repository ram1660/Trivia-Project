#include <iostream>
#include <vector>
class Question
{
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
public:
	std::string getQuestion();
	std::string getPossibleAnswers();
	std::string getCorrectAnswer();
};