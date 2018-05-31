#pragma once
#include <algorithm>
#include "structures.h"
#include "LoggedUser.h"

class Room
{
public:
	Room();
	Room(RoomData data);

	~Room();
	void addUser(string username);
	void removeUser(string usnername);
	vector<LoggedUser> getAllUsers() const;
	RoomData getMetaRoom() const;
	bool operator ==(Room const &other);
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};

