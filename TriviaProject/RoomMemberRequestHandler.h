#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler();
	~RoomMemberRequestHandler();
	bool isRequestRelevant(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	Room m_room;
	LoggedUser m_user;
	RoomManager m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult leaveRoom(Request r);
	RequestResult getRoomState(Request r);
};

