#include "RoomAdminRequestHandler.h"

RoomAdminRequestHandler::RoomAdminRequestHandler()
{
}

RoomAdminRequestHandler::RoomAdminRequestHandler(Room* room, LoggedUser roomOwner, RoomManager* roomManager, RequestHandlerFactory* handlerFactory) : m_room(room), m_roomManager(roomManager), m_user(roomOwner), m_handlerFactory(handlerFactory)
{
}


RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
	delete m_handlerFactory;
	delete m_room;
}

bool RoomAdminRequestHandler::isRequestRelevant(Request r)
{
	if (r.id == REQUEST_CLOSE_ROOM || r.id == REQUEST_START_ROOM || r.id == REQUEST_GET_ROOM_STATE)
		return true;
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(Request r)
{
	if (r.id == REQUEST_CLOSE_ROOM)
		return closeRoom(r);
	else if (r.id == REQUEST_START_ROOM)
		return startGame(r);
	else
		return getRoomState(r);
}

RequestResult RoomAdminRequestHandler::closeRoom(Request r)
{
	RequestResult result;
	Buffer buffer;
	CloseRoomResponse response;
	m_roomManager->deleteRoom(m_room->getMetaRoom()->id);
	response.status = RESPONSE_CLOSE_ROOM;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	result.newHandler = m_handlerFactory->createMenuRequestHandler();
	return result;
}

RequestResult RoomAdminRequestHandler::startGame(Request r)
{
	RequestResult result;
	Buffer buffer;
	StartRoomResponse response;
	m_room->getMetaRoom()->isActive = ROOM_STATUS_IN_A_PROGRESS;
	response.status = RESPONSE_START_ROOM;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}

RequestResult RoomAdminRequestHandler::getRoomState(Request r)
{
	RequestResult result;
	Buffer buffer;
	GetRoomStateResponse response;
	RoomData* roomMeta = m_room->getMetaRoom();
	response.status = RESPONSE_GET_ROOM_STATE;
	response.hasGameBegun = roomMeta->isActive;
	response.answerTimeout = roomMeta->timePerQuestion;
	for (size_t i = 0; i < m_room->getAllUsers().size(); i++)
		response.players[i] = m_room->getAllUsers()[i].getUsername();
	response.questionCount = roomMeta->questionCount;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}
