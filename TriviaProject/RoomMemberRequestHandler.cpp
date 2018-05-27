#include "RoomMemberRequestHandler.h"



RoomMemberRequestHandler::RoomMemberRequestHandler()
{
}


RoomMemberRequestHandler::~RoomMemberRequestHandler()
{
}

bool RoomMemberRequestHandler::isRequestRelevant(Request r)
{
	return false;
}

RequestResult RoomMemberRequestHandler::handleRequest(Request r)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::leaveRoom(Request r)
{
	return RequestResult();
}

RequestResult RoomMemberRequestHandler::getRoomState(Request r)
{
	return RequestResult();
}
