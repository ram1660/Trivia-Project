#include "LoginManager.h"

LoginManager::LoginManager()
{
}

LoginManager::LoginManager(IDatabase & db) : m_database(&db)
{
}


LoginManager::~LoginManager()
{
	delete m_database;
}

void LoginManager::signup(std::string username, std::string password, std::string email)
{
	// Some SQL queries.
	// Checking if the user exists.
	// If he doesn't exists then entering the info the database but not into LoggedUsers vector.
}

void LoginManager::login(std::string username, std::string password)
{
	// Some SQL queries.
	// Checking if the user exists.
	// If he is inserting him to LoggedUsers vector.
}

void LoginManager::logout()
{
	// Removing user from the vector.
	// How do I remove the user from the vector without a username?
}

std::vector<LoggedUser> LoginManager::getLoggedUsers() const
{
	return m_loggedUsers;
}

IDatabase & LoginManager::getDatabase() const
{
	return *m_database;
}
