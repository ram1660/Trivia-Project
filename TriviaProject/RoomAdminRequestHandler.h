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
	bool isRequestRelevant(const Request& r) override;
	RequestResult handleRequest(Request r) override;
private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult kickPlayer(const Request& r);
	RequestResult closeRoom(const Request& r);
	RequestResult startGame(const Request& r);
	RequestResult getRoomState(const Request& r);
};

