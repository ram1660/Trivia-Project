#include "Room.h"

Room::Room()
{
}

Room::~Room()
{
}

void Room::addUser(string username)
{
	// Check if the room is full?
	m_users.push_back(LoggedUser(username));
}

void Room::removeUser(string username)
{
	LoggedUser user(username);
	m_users.erase(remove(m_users.begin(), m_users.end(), user), m_users.end());
}

vector<LoggedUser> Room::getAllUsers() const
{
	return m_users;
}

RoomData Room::getMetaRoom() const
{
	return m_metadata;
}
