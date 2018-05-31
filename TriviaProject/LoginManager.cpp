#include "LoginManager.h"

LoginManager::LoginManager() : m_database(new IDatabase())
{
}

LoginManager::LoginManager(IDatabase & db) : m_database(&db)
{
}


LoginManager::~LoginManager()
{
	delete m_database;
}

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	// Some SQL queries.
	// Checking if the user exists.
	// If he doesn't exists then entering the info the database but not into LoggedUsers vector.
	// If he exists don't do nothing.
	return false;
}

bool LoginManager::login(std::string username, std::string password)
{
	// Some SQL queries.
	// Checking if the user exists.
	// If he is inserting him to LoggedUsers vector.
	// Else don't insert
	return false;
}

bool LoginManager::logout(std::string username)
{
	// Removing user from the vector.
	return false;
}

std::vector<LoggedUser*> LoginManager::getLoggedUsers() const
{
	return m_loggedUsers;
}

IDatabase & LoginManager::getDatabase() const
{
	return *m_database;
}
