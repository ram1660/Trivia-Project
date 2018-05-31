#pragma once
#include "LoginManager.h"
#include <iostream>
class User
{
public:
	User();
	~User();
	User(std::string name);
	std::string getUsername();
	std::string getEmail();
	std::string getPassword();

private:
	std::string m_username;
	std::string m_email;
	std::string m_password;

};

