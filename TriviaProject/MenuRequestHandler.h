#pragma once
#include "IRequestHandler.h"
#include "structures.h"
#include "LoggedUser.h"
#include "RequestHandlerFactory.h"
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler();
	~MenuRequestHandler();
	bool isRequestRelevant(Request r) override; // Update the protocol with menu codes.
	RequestResult handleRequest(Request r) override;
private:
	LoggedUser m_user;
	RoomManager m_roomManager;
	HighscoreTable* m_highscoreTable;
	RequestHandlerFactory m_handlerFactory;

	RequestResult signout(Request r);
	RequestResult getRooms(Request r);
	RequestResult getPlayerInRoom(Request r);
	RequestResult getHighscores(Request r);
	RequestResult joinRoom(Request r);
	RequestResult createRoom(Request r);
};

