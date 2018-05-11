#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "structures.h"
#include "LoginManager.h"
#include "HighscoreTable.h"
#include "RoomManager.h"
class RoomManager;
class MenuRequestHandler;
class HighscoreTable;
class LoginManager;
class LoginRequestHandler;
class RequestHandlerFactory
{
public:
	~RequestHandlerFactory();
	RequestHandlerFactory();
	RequestHandlerFactory(LoginManager* loginManager, RoomManager* roomManager, HighscoreTable* highScoreTable);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
private:
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	HighscoreTable* m_highscoreTable;
};

