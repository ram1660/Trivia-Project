#pragma once
#include <iostream>
class LoggedUser
{
public:
	LoggedUser();
	~LoggedUser();
	LoggedUser(std::string name);
	bool operator==(const LoggedUser &user) const;
	std::string getUsername() const;
private:
	std::string m_username;

};

