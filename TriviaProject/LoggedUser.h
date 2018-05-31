#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser();
	~LoggedUser();
	LoggedUser(std::string name);
	std::string getUsername();
private:
	std::string m_username;

};

