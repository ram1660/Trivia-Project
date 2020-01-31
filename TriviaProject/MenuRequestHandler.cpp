#include "MenuRequestHandler.h"

MenuRequestHandler::MenuRequestHandler()
{
}

MenuRequestHandler::MenuRequestHandler(LoginManager* loginManager, RoomManager * room, HighscoreTable *table, RequestHandlerFactory * factory) : m_loginManager(loginManager), m_roomManager(room), m_highscoreTable(table), m_handlerFactory(factory)
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
	else if (r.id == REQUEST_GET_ROOMS)
		return getRooms(r);
	else
		return signout(r);
}

RequestResult MenuRequestHandler::getRooms(Request r)
{
	RequestResult result;
	Buffer buffer;
	GetRoomsResponse response;
	vector<RoomData*> roomsData;
	for (auto room : m_roomManager->getRooms())
		roomsData.push_back(room);
	response.status = RESPONSE_GET_ROOMS;
	response.rooms = roomsData;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}

RequestResult MenuRequestHandler::signout(Request r)
{
	Buffer b, finalBuffer;
	b.buffer = r.buffer;
	vector<char> code, data;
	SignoutRequest request = JsonRequestPacketDeserializer::deserializeSignoutRequest(b);
	RequestResult result;
	GeneralResponse response;
	response.code = GENERAL_RESPONSE;
	b.buffer = r.buffer;
	m_loginManager->logout(request.username);
	code.push_back(GENERAL_RESPONSE);
	data = JsonResponsePacketSerializer::serializeResponse(response);
	finalBuffer.buffer.reserve(code.size() + data.size());
	finalBuffer.buffer.insert(finalBuffer.buffer.end(), code.begin(), code.end());
	finalBuffer.buffer.insert(finalBuffer.buffer.end(), data.begin(), data.end());
	result.response = finalBuffer;

	return result;
}


RequestResult MenuRequestHandler::getPlayersInRoom(Request r)
{
	RequestResult result;
	Buffer buff;
	buff.buffer = r.buffer;
	GetPlayersInRoomRequest roomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersRequest(buff);
	Room room;
	for (auto roomData : m_roomManager->getRooms())
		if (roomData->id == roomRequest.roomId)
			room = m_roomManager->getSpecificRoom(roomData->id);
	if (room.getMetaRoom()->id != INVALID_ROOM)
	{
		Room requestedRoom = m_roomManager->getSpecificRoom(room.getMetaRoom()->id);
		GetPlayersInRoomResponse response;
		vector<LoggedUser> vec = requestedRoom.getAllUsers();
		for (int i = 0; i < vec.size(); i++)
			response.rooms.push_back(vec[i].getUsername());
		Buffer b;
		b.buffer = JsonResponsePacketSerializer::serializeResponse(response);
		result.response = b;
		result.newHandler = nullptr;
	}
	else
	{
		ErrorResponse error;
		error.message = "ERROR: This room doesn't exists!";
		Buffer b;
		b.buffer = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult MenuRequestHandler::getHighscores(Request r)
{
	RequestResult result;
	Buffer buff;
	HighscoreResponse response;
	response.highscores = m_highscoreTable->getHighscores();
	response.status = RESPONSE_GET_HIGHSCORE;
	buff.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buff;
	return result;
}

RequestResult MenuRequestHandler::joinRoom(Request r)
{
	RequestResult result;
	Buffer buff;
	buff.buffer = r.buffer;
	JoinRoomRequest roomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(buff);
	RoomData dataRoom;
	bool isFound = false;
	dataRoom.id = roomRequest.roomId;
	for(RoomData* room : m_roomManager->getRooms())
	{
		if (dataRoom.id == room->id)
		{
			isFound = true;
			dataRoom = *room;
		}
	}
	if (!isFound)
	{
		ErrorResponse error;
		error.message = "ERROR: This room doesn't exists!";
		Buffer b;
		b.buffer = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	else
	{
		if (find(m_roomManager->getSpecificRoom(roomRequest.roomId).getAllUsers().begin(), m_roomManager->getSpecificRoom(roomRequest.roomId).getAllUsers().end(), LoggedUser(roomRequest.username)) == m_roomManager->getSpecificRoom(roomRequest.roomId).getAllUsers().end())
		{
			m_roomManager->getSpecificRoom(roomRequest.roomId).addUser(roomRequest.username);
			JoinRoomResponse response;
			response.status = RESPONSE_JOIN_ROOM;
			Buffer b;
			b.buffer = JsonResponsePacketSerializer::serializeResponse(response);
			result.response = b;
			result.newHandler = m_handlerFactory->createRoomMemberRequestHandler();
		}
		else
		{
			ErrorResponse error;
			error.message = "ERROR: User is already inside this room!";
			Buffer b;
			b.buffer = JsonResponsePacketSerializer::serializeResponse(error);
			result.response = b;
			result.newHandler = nullptr;
		}
	}

	return result;
}

RequestResult MenuRequestHandler::createRoom(Request r)
{
	RequestResult result;
	Buffer buff;
	CreateRoomResponse response;
	buff.buffer = r.buffer;
	CreateRoomRequest roomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(buff);
	LoggedUser roomCreator(roomRequest.username);
	m_roomManager->createRoom(roomCreator, roomRequest);
	response.status = RESPOSNSE_CREATE_ROOM;
	buff.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buff;
	return result;
}
