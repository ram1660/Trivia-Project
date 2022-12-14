#include "Room.h"

Room::Room(): m_metadata(new RoomData)
{
}

Room::Room(RoomData* data) : m_metadata(data)
{
}

Room::~Room()
{
	for (LoggedUser* user : m_users)
		delete user;
}

bool Room::addUser(string username) noexcept
{
	// Check if the room is full?
	if (m_users.size() == m_metadata->maxPlayers)
		return false;
	m_users.push_back(new LoggedUser(username));
	return true;
}

void Room::removeUser(string username) noexcept
{
	LoggedUser user(username);
	m_users.erase(remove(m_users.begin(), m_users.end(), &user), m_users.end());
}

vector<LoggedUser*> Room::getAllUsers() const
{
	return m_users;
}

RoomData* Room::getMetaRoom() const
{
	return m_metadata;
}

bool Room::operator==(Room & other) const
{
	return (this->getMetaRoom()->id == other.getMetaRoom()->id);
}
