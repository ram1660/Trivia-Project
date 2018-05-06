#pragma once
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
class LoginManager
{
public:
	void signup(std::string name, std::string something, std::string anothersomething);
	void login(std::string name, std::string anothername);
	void logout();
private:
	IDatabase& m_database;
	std::vector<LoggedUser> m_loggedUsers;
};

