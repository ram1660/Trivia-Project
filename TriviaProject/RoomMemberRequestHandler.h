#pragma once
#include "IRequestHandler.h"
#include "Room.h"
#include "Protocol.h"
#include "JsoneResponsePacketSerializer.h"
class RequestHandlerFactory;
class RoomManager;
class RoomMemberRequestHandler : public IRequestHandler
{
public:
	RoomMemberRequestHandler();
	RoomMemberRequestHandler(Room *room, LoggedUser user, RoomManager* roomManager, RequestHandlerFactory* factory);
	~RoomMemberRequestHandler();
	bool isRequestRelevant(const Request& r) override;
	RequestResult handleRequest(Request r) override;
private:
	Room* m_room;
	LoggedUser m_user;
	RoomManager* m_roomManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult leaveRoom(Request r);
	RequestResult getRoomState(Request r);
};

