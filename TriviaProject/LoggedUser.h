#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser();
	~LoggedUser();
	LoggedUser(std::string name);
	bool operator==(LoggedUser const &user);
	std::string getUsername();
private:
	std::string m_username;
};

