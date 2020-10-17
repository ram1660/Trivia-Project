#pragma once
#include "structures.h"
#include "LoggedUser.h"
#include "Room.h"

#define INVALID_ROOM -1

class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	void createRoom(LoggedUser& user, CreateRoomRequest roomInfo); // Possibly an admin?
	void deleteRoom(unsigned int roomId);
	inline unsigned int getRoomState(int ID) const; // Not clear what that's mean.
	vector<RoomData*> getRooms() const; // What is that mean RoomMetadata?
	Room getSpecificRoom(int id) const;
	Room getUserRoom(string user) const;
private:
	map<unsigned int, Room> m_rooms;
	bool isRoomExists(unsigned int id);
};

