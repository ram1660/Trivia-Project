#include "MenuRequestHandler.h"



MenuRequestHandler::MenuRequestHandler()
{
}


MenuRequestHandler::~MenuRequestHandler()
{
	delete m_highscoreTable;
}

bool MenuRequestHandler::isRequestRelevant(Request r)
{
	return false;
}

RequestResult MenuRequestHandler::handleRequest(Request r)
{
	return RequestResult();
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
