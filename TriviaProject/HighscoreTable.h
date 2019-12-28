#pragma once
#include "SqliteDatabase.h"
class IDatabase;
class LoggedUser;
class HighscoreTable : public IDatabase
{
public:
	HighscoreTable();
	HighscoreTable(IDatabase * db);
	~HighscoreTable();
	std::map<LoggedUser, int> getHighscores();
	bool doesUserExists(std::string username) override;
	void createUser(std::string username, std::string password, std::string email) override;
	void deleteUser(LoggedUser& user) override;
	bool DoesPasswordMatchUser(std::string username, std::string password) override;

	//questions

	bool open() override;
	void clear() override;

private:
	IDatabase * m_database;
};

