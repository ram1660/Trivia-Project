#include "LoginManager.h"

LoginManager::LoginManager() : m_database(new SqliteDatabase())
{
	m_database->open();
}

LoginManager::LoginManager(IDatabase & db) : m_database(&db)
{
	m_database->open();
}


LoginManager::~LoginManager()
{
	delete m_database;
}

bool LoginManager::signup(std::string username, std::string password, std::string email)
{
	if (m_database->doesUserExists(username))
		return false;
	m_database->createUser(username, password, email);
	LoggedUser newUser(username);
	m_loggedUsers.push_back(newUser);
	// Some SQL queries.
	// Checking if the user exists.
	// If he doesn't exists then entering the info the database but not into LoggedUsers vector.
	// If he exists don't do nothing.
	return true;
}

bool LoginManager::login(std::string username, std::string password)
{
	if (m_database->doesUserExists(username) && m_database->DoesPasswordMatchUser(username, password))
	{
		LoggedUser user(username);
		m_loggedUsers.push_back(user);
		return true;
	}
	// Some SQL queries.
	// Checking if the user exists.
	// If he is inserting him to LoggedUsers vector.
	// Else don't insert
	return false;
}

bool LoginManager::logout(std::string username)
{
	for (size_t i = 0; i < m_loggedUsers.size(); i++)
	{
		if (m_loggedUsers[i] == username)
		{
			m_loggedUsers.erase(m_loggedUsers.begin() + i);
			return true;
		}
	}
	return false;
}

std::vector<LoggedUser> LoginManager::getLoggedUsers() const
{
	return m_loggedUsers;
}

IDatabase & LoginManager::getDatabase() const
{
	return *m_database;
}
