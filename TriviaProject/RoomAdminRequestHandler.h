#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler();
	~RoomAdminRequestHandler();
	bool isRequestRelevant(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager m_roomManager;
	RequestHandlerFactory m_handlerFactory;
	RequestResult closeRoom(Request r);
	RequestResult startGame(Request r);
	RequestResult getRoomState(Request r);
};

