#include <iostream>
#include <vector>
class Question
{
private:
	std::string m_question;
	std::vector<std::string> m_possibleAnswers;
public:
	Question(std::string question, std::string correct_ans, std::string ans1, std::string ans2, std::string ans3);
	std::string getQuestion();
	std::string getPossibleAnswers();
	std::string getCorrectAnswer();
};