#pragma once
#include "structures.h"
#include "LoggedUser.h"
#include "Room.h"
class RoomManager
{
public:
	RoomManager();
	~RoomManager();
	void createRoom(LoggedUser user); // Possibly an admin?
	void deleteRoom(); // With what parameters can we delete a room from a map if we don't have a key.
	unsigned int getRoomState(int ID); // Not clear what that's mean.
	std::vector<RoomMetadata> getRooms(); // What is that mean RoomMetadata?
private:
	std::map<roomID, Room> m_rooms; // roomID could be unsigned int?
};

