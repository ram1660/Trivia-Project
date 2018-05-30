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
	void deleteRoom(unsigned int roomId); // With what parameters can we delete a room from a map if we don't have a key.
	unsigned int getRoomState(int ID) const; // Not clear what that's mean.
	//vector<RoomMetaData> getRooms(); // What is that mean RoomMetadata?
	map<unsigned int, Room> getRooms() const;
	Room getSpecificRoom(int id);
private:
	map<unsigned int, Room> m_rooms; // roomID could be unsigned int?
};

