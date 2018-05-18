#include "Room.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::addUser(string username)
{
	m_users.push_back(LoggedUser(username));
}

void Room::removeUser(string username)
{
	m_users.erase(std::remove(m_users.begin(), m_users.end(), LoggedUser(username)), m_users.end());
}

vector<LoggedUser> Room::getAllUsers()
{
	return m_users;
}
