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

bool LoggedUser::operator==(LoggedUser const & user)
{
	if (this->m_username == user.m_username)
		return true;
	return false;
}

std::string LoggedUser::getUsername()
{
	return m_username;
}
