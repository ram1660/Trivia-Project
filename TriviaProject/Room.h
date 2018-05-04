#pragma once
#include "structures.h"
#include "LoggedUser.h"
class Room
{
public:
	Room();
	~Room();
	void addUser();
	void removeUser();
	void getAllUsers();
private:
	RoomData m_metadata;
	vector<LoggedUser> m_users;
};

