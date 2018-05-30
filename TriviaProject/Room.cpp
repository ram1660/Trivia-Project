#include "Room.h"

Room::Room() 
{
}

Room::Room(RoomData data) : m_metadata(data)
{
}

Room::~Room()
{
}

void Room::addUser(string username)
{
	// Check if the room is full?
	if (m_users.size() == m_metadata.maxPlayers)
		cout << "The room is full!" << endl;
	else
	{
		 m_users.push_back(LoggedUser(username));
		 cout << "Player has joined to the room!" << endl;
	}
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
