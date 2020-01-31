#pragma once
#include "IRequestHandler.h"
#include "RequestHandlerFactory.h"
#include "JsoneResponsePacketSerializer.h"
class RoomAdminRequestHandler : public IRequestHandler
{
public:
	RoomAdminRequestHandler();
	RoomAdminRequestHandler(Room* room, LoggedUser roomOwner, RoomManager* roomManager, RequestHandlerFactory* handlerFactory);
	~RoomAdminRequestHandler();
	bool isRequestRelevant(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult closeRoom(Request r);
	RequestResult startGame(Request r);
	RequestResult getRoomState(Request r);
};

