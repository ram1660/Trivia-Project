#include "RoomManager.h"



RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser user)
{

}

void RoomManager::deleteRoom()
{
}

unsigned int RoomManager::getRoomState(int ID) const
{
	unsigned int state = m_rooms.at(ID).getMetaRoom().isActive;
	return state;
}

//std::vector<RoomMetadata> RoomManager::getRooms()
//{
//	return std::vector<RoomMetadata>();
//}
