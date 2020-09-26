#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "structures.h"
#include "LoginManager.h"
#include "HighscoreTable.h"
#include "RoomManager.h"
#include "RoomMemberRequestHandler.h"
#include "RoomAdminRequestHandler.h"
#include "GameRequestHandler.h"
class RoomManager;
class MenuRequestHandler;
class HighscoreTable;
class LoginManager;
class LoginRequestHandler;
class RoomAdminRequestHandler;
class RoomMemberRequestHandler;
class GameRequestHandler;
class RequestHandlerFactory
{
public:
	~RequestHandlerFactory();
	RequestHandlerFactory();
	RequestHandlerFactory(LoginManager* loginManager, RoomManager* roomManager, HighscoreTable* highScoreTable);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
	RoomAdminRequestHandler* createRoomAdminRequestHandler();
	RoomMemberRequestHandler* createRoomMemberRequestHandler();
	GameRequestHandler* createGameRequestHandler();
private:
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	HighscoreTable* m_highscoreTable;
	GameManager* m_gameManager;
};

