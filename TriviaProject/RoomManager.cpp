#include "RoomManager.h"


RoomManager::RoomManager()
{
}


RoomManager::~RoomManager()
{
}

void RoomManager::createRoom(LoggedUser& user, CreateRoomRequest roomInfo)
{
	RoomData data;
	for (unsigned int i = 0; i < m_rooms.rbegin()->first; i++)
		if (!isRoomExists(i))
		{
			data.id = i;
			data.isActive = ROOM_STATUS_WAITING;
			data.maxPlayers = roomInfo.maxUsers;
			data.name = roomInfo.roomName;
			data.timePerQuestion = roomInfo.answerTimeout;
			data.questionCount = roomInfo.questionCount;
			Room room(&data);
			m_rooms.insert({ i, room });
		}
}

void RoomManager::deleteRoom(unsigned int roomId)
{
	m_rooms.erase(roomId);
}

inline unsigned int RoomManager::getRoomState(int ID) const
{
	return m_rooms.at(ID).getMetaRoom()->isActive;
}


Room RoomManager::getSpecificRoom(int id) const
{
	RoomData data;
	data.id = INVALID_ROOM;
	Room room(&data);
	for (unsigned int i = 0; i < m_rooms.size(); i++)
		if (m_rooms.at(i).getMetaRoom()->id == id)
			return m_rooms.at(i);
	return room;
}

Room RoomManager::getUserRoom(string user) const
{
	LoggedUser targetUser(user);
	for (auto room : m_rooms)
		if (find(room.second.getAllUsers().begin(), room.second.getAllUsers().end(), &targetUser) != room.second.getAllUsers().end())
			return room.second;
	return Room();
}

bool RoomManager::isRoomExists(unsigned int id)
{
	return (m_rooms.find(id) == m_rooms.end()) ? false : true;
}

std::vector<RoomData*> RoomManager::getRooms() const
{
	vector<RoomData*> roomsData;
	for (auto room : m_rooms)
		roomsData.push_back(room.second.getMetaRoom());
	return roomsData;
}
