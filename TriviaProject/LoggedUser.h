#pragma once
#include "LoginManager.h"
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

