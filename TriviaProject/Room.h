#pragma once
#include <algorithm>
#include "structures.h"
#include "LoggedUser.h"

class Room
{
public:
	Room();
	~Room();
	void addUser(string username);
	void removeUser(string usnername);
	vector<LoggedUser> getAllUsers() const;
	RoomData getMetaRoom() const;
	
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};

