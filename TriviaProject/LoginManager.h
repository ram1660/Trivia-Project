#pragma once
#include <vector>
#include "LoggedUser.h"
#include "IDatabase.h"
class LoginManager
{
public:
	LoginManager();
	LoginManager(IDatabase& db);
	~LoginManager();
	bool signup(std::string username, std::string password, std::string email);
	bool login(std::string username, std::string password);
	bool logout(std::string username);
	std::vector<LoggedUser*> getLoggedUsers() const;
	IDatabase& getDatabase() const;
private:
	IDatabase* m_database;
	std::vector<LoggedUser*> m_loggedUsers;
};

