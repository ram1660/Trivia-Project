#pragma once
#include "IRequestHandler.h"
#include "structures.h"
#include "RequestHandlerFactory.h"
#include <algorithm>

class LoggedUser;
class RoomManager;
class RequestHandlerFactory;
class HighscoreTable;
class LoginManager;
class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler() = delete;
	MenuRequestHandler(LoginManager* loginManager, RoomManager* room, HighscoreTable* table, RequestHandlerFactory* factory);
	~MenuRequestHandler();
	bool isRequestRelevant(const Request& r) override;
	RequestResult handleRequest(Request r) override;
private:
	LoggedUser* m_user;
	RoomManager* m_roomManager;
	HighscoreTable* m_highscoreTable;
	RequestHandlerFactory* m_handlerFactory;
	LoginManager* m_loginManager;

	RequestResult signout(Request r);
	RequestResult getRooms(Request r);
	RequestResult getPlayersInRoom(Request r);
	RequestResult getHighscores(Request r);
	RequestResult joinRoom(const Request& r);
	RequestResult createRoom(Request r);
};

