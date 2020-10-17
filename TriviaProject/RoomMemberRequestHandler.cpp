#include "RoomMemberRequestHandler.h"

RoomMemberRequestHandler::RoomMemberRequestHandler()
{
}

RoomMemberRequestHandler::RoomMemberRequestHandler(Room* room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* factory) : m_room(room), m_user(user), m_roomManager(roomManager), m_handlerFactory(factory)
{
}


RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(const Request& r)
{
	if (r.id == REQUEST_LEAVE_ROOM || r.id == REQUEST_GET_ROOM_STATE)
		return true;
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(Request r)
{
	if (r.id == REQUEST_LEAVE_ROOM)
		return leaveRoom(r);
	else
		return getRoomState(r);
}

RequestResult RoomMemberRequestHandler::leaveRoom(Request r)
{
	RequestResult result;
	Buffer buffer;
	LeaveRoomResponse response;
	m_room->removeUser(m_user.getUsername());
	response.status = RESPONSE_LEAVE_ROOM;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}

RequestResult RoomMemberRequestHandler::getRoomState(Request r)
{
	RequestResult result;
	Buffer buffer;
	GetRoomStateResponse response;
	RoomData* roomMeta = m_room->getMetaRoom();
	response.status = RESPONSE_GET_ROOM_STATE;
	response.hasGameBegun = roomMeta->isActive;
	response.answerTimeout = roomMeta->timePerQuestion;
	for (size_t i = 0; i < m_room->getAllUsers().size(); i++)
		response.players[i] = m_room->getAllUsers()[i]->getUsername();
	response.questionCount = roomMeta->questionCount;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}
