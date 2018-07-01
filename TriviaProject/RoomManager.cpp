#include "RoomManager.h"
#define INVALID_ROOM_ID 9999


RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser user)
{

}

void RoomManager::deleteRoom(unsigned int roomId)
{

}

unsigned int RoomManager::getRoomState(int ID) const
{
	unsigned int state = m_rooms.at(ID).getMetaRoom().isActive;
	return state;
}

map<unsigned int, Room> RoomManager::getRooms() const
{
	return m_rooms;
}

Room RoomManager::getSpecificRoom(int id)
{
	RoomData data;
	data.id = INVALID_ROOM_ID;
	Room room(data);
	for (int i = 0; i < m_rooms.size(); i++)
		if (m_rooms[i].getMetaRoom().id == id)
			return m_rooms[i];
	return room;
}

Room RoomManager::getUserRoom(string user)
{
	LoggedUser targetUser(user);
	for (auto room : m_rooms)
		if (find(room.second.getAllUsers().begin(), room.second.getAllUsers().end(), targetUser) != room.second.getAllUsers().end())
			return room.second;
}

//std::vector<RoomMetadata> RoomManager::getRooms()
//{
//	return std::vector<RoomMetadata>();
//}
