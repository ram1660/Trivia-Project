#pragma once
#include <algorithm>
#include "IDatabase.h"
#include "sqlite3.h"
class SqliteDatabase : public IDatabase
{
public:
	//std::list<Question> getQuestions (int);
	//std::map<LoggedUser, int> getHighscores();
	SqliteDatabase();
	~SqliteDatabase();
	//user
	bool doesUserExists(std::string username) override;
	void createUser(std::string username, std::string password, std::string email) override;
	void deleteUser(LoggedUser& user) override;
	bool DoesPasswordMatchUser(std::string username, std::string password) override;
	//questions
	std::vector<Question> generateRandomQuestions() override;

	bool open() override;
	void clear() override;
	sqlite3* getDatabase() override;
private:
	std::list<LoggedUser> m_users;
	std::list<Question> m_question;
	int getQuestionsSize();
	// Callbacks

	static int doesUserExistsCallback(void* data, int argc, char** argv, char** azColName);
	static int callbackUser(void* data, int argc, char** argv, char** azColName);
	static int callbackQuestion(void* data, int argc, char** argv, char** azColName);
	static int callbackQuestionsSize(void* data, int argc, char** argv, char** azColName);
	static int callbackSelectQuestions(void* data, int argc, char** argv, char** azColName);
	//int callbackUser(void* data, int argc, char** argv, char** azColName);


	sqlite3 * db;
};
