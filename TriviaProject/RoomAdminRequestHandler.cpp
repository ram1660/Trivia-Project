#include "RoomAdminRequestHandler.h"



RoomAdminRequestHandler::RoomAdminRequestHandler()
{
}


RoomAdminRequestHandler::~RoomAdminRequestHandler()
{
}

bool RoomAdminRequestHandler::isRequestRelevant(Request r)
{
	return false;
}

RequestResult RoomAdminRequestHandler::handleRequest(Request r)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::closeRoom(Request r)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::startGame(Request r)
{
	return RequestResult();
}

RequestResult RoomAdminRequestHandler::getRoomState(Request r)
{
	return RequestResult();
}
