#include <map>
#include <algorithm>
#include "SqliteDatabase.h"
int callbackUser(void *data, int argc, char **argv, char **azColName);
int callbackQuestion(void *data, int argc, char **argv, char **azColName);
std::list<LoggedUser> m_users;
std::list<Question> m_question;

bool SqliteDatabase::open()
{
	std::string dbFileName = "MyDB.sqlite";

	int doesFileExist = _access(dbFileName.c_str(), 0);
	int res = sqlite3_open(dbFileName.c_str(), &db);
	if (res != SQLITE_OK)
	{
		db = nullptr;
		std::cout << "Failed to open DB" << std::endl;
		return false;
	}

	if (doesFileExist == -1)
	{
		std::cout << "Database did not found create new one" << std::endl;
		const char* sqlUsers = "CREATE TABLE 'USER' ('USERNAME' TEXT NOT NULL UNIQUE, PASSWORD TEXT NOT NULL, MAIL TEXT NOT NULL, PRIMARY KEY('USERNAME'));";
		const char* sqlQuestions = "CREATE TABLE 'QUESTION' ('QUESTION_ID' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'QUESTION' TEXT NOT NULL UNIQUE, 'CORRECT_ANS' TEXT NOT NULL, 'ANS1' TEXT NOT NULL, 'ANS2' TEXT NOT NULL, 'ANS3' TEXT NOT NULL, 'ANS4' TEXT NOT NULL);";
		const char* sqlGame = "CREATE TABLE 'GAME' ('GAME_ID' INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT, 'STATUS' INTEGER NOT NULL, 'START_TIME' TEXT, 'END_TIME' TEXT);";
		char** errMessage = nullptr;
		res = sqlite3_exec(db, sqlUsers, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "Could not create the user table!";
			return false;
		}
		res = sqlite3_exec(db, sqlQuestions, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "Could not create the question table!";
			return false;
		}
		res = sqlite3_exec(db, sqlGame, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "Could not create the game table!";
			return false;
		}
	}
	return true;
}

void SqliteDatabase::clear()
{
	m_users.clear();
}

// ******************* User ******************* 

void SqliteDatabase::createUser(std::string username, std::string password, std::string email)
{
	m_users.clear();
	std::string sql = "INSERT INTO USER VALUES ('" + username + "', '" + password + "', '" + email + "');";
	const char* sqlStatement = sql.c_str();
	char *errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		std::cout << "Something is wrong!" << std::endl;
	}
}

void SqliteDatabase::deleteUser(LoggedUser& user)
{
	m_users.clear();
	if (doesUserExists(user.getUsername()))
	{

		std::string sql = "DELETE FROM USER WHERE NAME LIKE '" + user.getUsername() + "';";
		const char* sqlStatement = sql.c_str();
		char *errMessage = nullptr;
		int res = sqlite3_exec(db, sqlStatement, nullptr, nullptr, &errMessage);
		if (res != SQLITE_OK)
		{
			std::cout << "Something is wrong!" << std::endl;
		}
	}
}

SqliteDatabase::SqliteDatabase()
{
}

SqliteDatabase::~SqliteDatabase()
{
	sqlite3_close(db);
	delete db;
}

bool SqliteDatabase::doesUserExists(std::string username)
{
	std::string sqlStatement = "SELECT EXISTS (SELECT 1 from USER WHERE USERNAME = '" + username + "');";
	char* errMessage = nullptr;
	bool isExists = false;
	int res = sqlite3_exec(db, sqlStatement.c_str(), doesUserExistsCallback, &isExists, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Something is wrong!" << std::endl;
	return isExists;
}

bool SqliteDatabase::DoesPasswordMatchUser(std::string username, std::string password)
{
	std::string sqlStatement = "SELECT EXISTS (SELECT 1 from user WHERE username = '" + username + "' AND password = '" + password + "');";
	char* errMessage = nullptr;
	bool isMatch = false;
	int res = sqlite3_exec(db, sqlStatement.c_str(), doesUserExistsCallback, &isMatch, &errMessage);
	if (res != SQLITE_OK)
		std::cout << "Something is wrong!" << std::endl;
	return isMatch;
}

int SqliteDatabase::callbackUser(void * data, int argc, char ** argv, char ** azColName)
{
	std::string name;
	std::string gmail;
	std::string password;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "username")
		{
			name = (argv[i]);
		}
		else if (std::string(azColName[i]) == "mail")
		{
			gmail = (argv[i]);
		}
		else if (std::string(azColName[i]) == "PASSWORD")
		{
			password = (argv[i]);
		}
	}
	LoggedUser user(name);
	m_users.push_back(user);
	return 0;

}

int SqliteDatabase::doesUserExistsCallback(void * data, int argc, char ** argv, char ** azColName)
{
	bool* isExists = (bool*)data;
	if (argv[0] == "0")
	{
		*isExists = false;
	}
	else if (argv[0] == "1")
	{
		*isExists = true;
	}
	return 0;
}

int callbackQuestion(void *data, int argc, char **argv, char **azColName)
{
	std::string question;
	std::string correct_ans;
	std::string ans1;
	std::string ans2;
	std::string ans3;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "QUESTION")
		{
			question = (argv[i]);
		}
		else if (std::string(azColName[i]) == "CORRECT_ANS")
		{
			correct_ans = (argv[i]);
		}
		else if (std::string(azColName[i]) == "ANS1")
		{
			ans1 = (argv[i]);
		}
		else if (std::string(azColName[i]) == "ANS2")
		{
			ans2 = (argv[i]);
		}
		else if (std::string(azColName[i]) == "ANS3")
		{
			ans3 = (argv[i]);
		}
	}
	Question q(question, correct_ans, ans1, ans2, ans3);
	m_question.push_back(q);
	return 0;

}