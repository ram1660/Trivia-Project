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
	if (r.id == REQUEST_JOIN_ROOM || r.id == REQUEST_CREATE_ROOM || r.id == REQUEST_GET_HIGHSCORE || r.id == REQUEST_GET_MY_STATUS)
		return true;
	return false;
}

RequestResult MenuRequestHandler::handleRequest(Request r)
{
	
}

RequestResult MenuRequestHandler::signout(Request r)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getRooms(Request r)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getPlayerInRoom(Request r)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::getHighscores(Request r)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::joinRoom(Request r)
{
	return RequestResult();
}

RequestResult MenuRequestHandler::createRoom(Request r)
{
	return RequestResult();
}
