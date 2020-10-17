#pragma once
#include <algorithm>
#include "structures.h"
#include "LoggedUser.h"

class Room
{
public:
	Room();
	Room(RoomData* data);

	~Room();
	bool addUser(string username) noexcept;
	void removeUser(string usnername) noexcept;
	vector<LoggedUser*> getAllUsers() const;
	RoomData* getMetaRoom() const;
	bool operator ==(Room &other) const;
private:
	RoomData* m_metadata;
	vector<LoggedUser*> m_users;
};

