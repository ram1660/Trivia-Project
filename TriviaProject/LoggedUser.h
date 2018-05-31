#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser();
	~LoggedUser();
	LoggedUser(std::string name);
	bool operator==(const LoggedUser &user);
	std::string getUsername();
private:
	std::string m_username;

};

