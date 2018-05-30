#include "MenuRequestHandler.h"



MenuRequestHandler::MenuRequestHandler()
{
}

MenuRequestHandler::MenuRequestHandler(LoggedUser * user, RoomManager * room, HighscoreTable * table, RequestHandlerFactory * factory) : m_user(user), m_roomManager(room), m_highscoreTable(table), m_handlerFactory(factory)
{
}


MenuRequestHandler::~MenuRequestHandler()
{
	delete m_highscoreTable;
	delete m_roomManager;
	delete m_handlerFactory;
	delete m_user;
}

bool MenuRequestHandler::isRequestRelevant(Request r)
{
	if (r.id == REQUEST_JOIN_ROOM || r.id == REQUEST_CREATE_ROOM || r.id == REQUEST_GET_HIGHSCORE || r.id == REQUEST_GET_MY_STATS || r.id == REQUEST_SIGNOUT)
		return true;
	return false;
}

RequestResult MenuRequestHandler::handleRequest(Request r)
{
	RequestResult result;
	Buffer b;
	b.buffer = r.buffer;
	if (r.id == REQUEST_JOIN_ROOM)
		return joinRoom(r);
	else if (r.id == REQUEST_CREATE_ROOM)
		return createRoom(r);
	else if (r.id == REQUEST_GET_HIGHSCORE)
		return getHighscores(r);
	else
		return signout(r);
}

RequestResult MenuRequestHandler::signout(Request r)
{
	RequestResult result;
	Buffer buff;
	buff.buffer = r.buffer;
	// Missing function.
	LogoutResponse roomRequest = JsonRequestPacketDeserializer::deserializeJLogoutRequest(r);
	if (m_roomManager->) // statement may be removed because the designed of the client.
	{
		LogoutResponse response;
		response.status = RESPONSE_SIGNOUT;
		//Buffer b = JsonResponsePacketSerializer::serializeResponse(response);
		//result.response = b;
		//result.newHandler = m_handlerFactory->
	}
	else
	{
		ErrorResponse error;
		error.message = "ERROR: This user doesn't exists!";
		Buffer b = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult MenuRequestHandler::getRooms(Request r)
{
	RequestResult result;
	Buffer buffer;
	map<unsigned int, Room> rooms = m_roomManager->getRooms();
	
	return result;
}

RequestResult MenuRequestHandler::getPlayersInRoom(Request r)
{
	RequestResult result;
	Buffer buff;
	buff.buffer = r.buffer;
	GetPlayersInRoomRequest roomRequest;
	// Missing function.
	//GetPlayersInRoomRequest roomRequest = JsonRequestPacketDeserializer::deserializeJGetPlayersRequest(r);
	auto it = m_roomManager->getRooms().find(roomRequest.roomId);
	if (it != m_roomManager->getRooms().end())
	{
		GetPlayersInRoomResponse response;
		vector<LoggedUser> vec = it->second.getAllUsers();
		for (int i = 0; i < vec.size(); i++)
			response.rooms.push_back(vec[i].getUsername());
		//Buffer b = JsonResponsePacketSerializer::serializeResponse(response);
		//result.response = b;
		//result.newHandler = m_handlerFactory->
	}
	else
	{
		ErrorResponse error;
		error.message = "ERROR: This room doesn't exists!";
		Buffer b = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult MenuRequestHandler::getHighscores(Request r)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(Request r)
{
	RequestResult result;
	Buffer buff;
	buff.buffer = r.buffer;
	JoinRoomRequest roomRequest;
	RoomData dataRoom;
	dataRoom.id = roomRequest.roomId;
	// Missing function.
	//JoinRoomRequest roomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(r);
	if (find(m_roomManager->getRooms().begin(), m_roomManager->getRooms().end(), Room(dataRoom)) == m_roomManager->getRooms().end())
	{
		ErrorResponse error;
		error.message = "ERROR: This room doesn't exists!";
		Buffer b = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	else if (find(m_roomManager->getSpecificRoom(roomRequest.roomId).getAllUsers().begin(), m_roomManager->getSpecificRoom(roomRequest.roomId).getAllUsers().end(), LoggedUser(roomRequest.username)) != m_roomManager->getSpecificRoom(roomRequest.roomId).getAllUsers().end())
	{
		m_roomManager->getSpecificRoom(roomRequest.roomId).addUser(roomRequest.username);
		JoinRoomResponse response;
		response.status = RESPONSE_JOIN_ROOM;
		//Buffer b = JsonResponsePacketSerializer::serializeResponse(response);
		//result.response = b;
		result.newHandler = m_handlerFactory->createRoomMemberRequestHandler();
	}
	else
	{
		ErrorResponse error;
		error.message = "ERROR: User is already inside this room!";
		Buffer b = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult MenuRequestHandler::createRoom(Request r)
{
	RequestResult result;
	Buffer buff;
	buff.buffer = r.buffer;
	CreateRoomRequest roomRequest;
	// Missing functions.
	//CreateRoomRequest roomRequest = JsonRequestPacketDeserializer::deserializeRoomRequest(buff);
	//result.response = JsonResponsePacketSerializer::serializeResponse(roomRequest);
	//m_roomManager->createRoom(); // No idea why createRoom needs LoggedUser.
	return result;
}
