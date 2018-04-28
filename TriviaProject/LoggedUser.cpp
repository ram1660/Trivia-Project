#include "LoggedUser.h"



LoggedUser::LoggedUser()
{
}


LoggedUser::~LoggedUser()
{
}

LoggedUser::LoggedUser(std::string name) : m_username(name)
{
}

std::string LoggedUser::getUsername()
{
	return m_username;
}
