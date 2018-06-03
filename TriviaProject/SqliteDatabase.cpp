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
		return -1;
	}

	if (doesFileExist == 1)
	{

		const char* sqlUsers = "CREATE TABLE USERS (NAME INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL , GMAIL TEXT NOT NULL, PASSWORD TEXT NOT NULL);";
		const char* sqlQuestions = "CREATE TABLE QUESTIONS (NAME INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL , QUESTION TEXT NOT NULL, CORRECT_ANS TEXT NOT NULL, ANS1 TEXT NOT NULL, ANS2 TEXT NOT NULL, ANS3 TEXT NOT NULL);";

		char** errMessage = nullptr;
		res = sqlite3_exec(db, sqlUsers, nullptr, nullptr, errMessage);
		if (res != SQLITE_OK)
			return false;
	}


	sqlite3_close(db);
	db = nullptr;
	return 0;





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
	std::string sql = "INSERT INTO USERS VALUES {" + username + "," + email + "," + password + "};";
	const char* sqlStatement = sql.c_str();
	char *errMessage = nullptr;
	int res = sqlite3_exec(db, sqlStatement, callbackUser, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{

	}
}

void SqliteDatabase::deleteUser(LoggedUser& user)
{
	m_users.clear();
	if (doesUserExists(user.getUsername()))
	{

		std::string sql = "DELETE FROM USERS WHERE NAME LIKE" + user.getUsername() + ";";
		const char* sqlStatement = sql.c_str();
		char *errMessage = nullptr;
		int res = sqlite3_exec(db, sqlStatement, callbackUser, nullptr, &errMessage);
		if (res != SQLITE_OK)
		{

		}
	}
}

SqliteDatabase::SqliteDatabase()
{
}

SqliteDatabase::~SqliteDatabase()
{
}

bool SqliteDatabase::doesUserExists(std::string username)
{
	std::string sqlStatement = "SELECT EXISTS (SELECT 1 from USERS WHERE NAMES = '" + username + "');";
	char* errMessage = nullptr;

	int res = sqlite3_exec(db, sqlStatement.c_str(), callbackUser, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	} //Did it work?

	return bool(res);
}

bool SqliteDatabase::DoesPasswordMatchUser(std::string username, std::string password)
{
	std::string sqlStatement = "SELECT EXISTS (SELECT 1 from users WHERE name = '" + username + "' AND password = '" + password + "');";
	char* errMessage = nullptr;

	int res = sqlite3_exec(db, sqlStatement.c_str(), callbackUser, nullptr, &errMessage);
	if (res != SQLITE_OK)
	{
		return false;
	} //Did it work?

	return bool(res);
}

int callbackUser(void *data, int argc, char **argv, char **azColName)
{
	std::string name;
	std::string gmail;
	std::string password;
	for (int i = 0; i < argc; i++)
	{
		if (std::string(azColName[i]) == "NAME")
		{
			name = (argv[i]);
		}
		else if (std::string(azColName[i]) == "GMAIL")
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