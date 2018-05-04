#pragma once
#include "LoginRequestHandler.h"
#include "MenuRequestHandler.h"
#include "structures.h"
#include "LoginManager.h"
#include "HighscoreTable.h"
#include "RoomManager.h"
class RequestHandlerFactory
{
public:
	~RequestHandlerFactory();
	RequestHandlerFactory();
	RequestHandlerFactory(LoginManager* manager);
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();
private:
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	HighscoreTable* m_highscoreTable;
};

