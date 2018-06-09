#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* login = new LoginRequestHandler(m_loginManager, this);
	return login;
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	MenuRequestHandler* menu = new MenuRequestHandler();
	return menu;
}

RoomAdminRequestHandler * RequestHandlerFactory::createRoomAdminRequestHandler()
{
	RoomAdminRequestHandler* roomAdmin = new RoomAdminRequestHandler();
	return roomAdmin;
}

RoomMemberRequestHandler * RequestHandlerFactory::createRoomMemberRequestHandler()
{
	RoomMemberRequestHandler* roomMember = new RoomMemberRequestHandler();
	return roomMember;
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_loginManager;
	delete m_highscoreTable;
	delete m_roomManager;
}

RequestHandlerFactory::RequestHandlerFactory() : m_loginManager(nullptr), m_highscoreTable(nullptr), m_roomManager(nullptr)
{
}

RequestHandlerFactory::RequestHandlerFactory(LoginManager* loginManager, RoomManager* roomManager, HighscoreTable* highScoreTable) : m_loginManager(loginManager), m_roomManager(roomManager), m_highscoreTable(highScoreTable)
{
}
