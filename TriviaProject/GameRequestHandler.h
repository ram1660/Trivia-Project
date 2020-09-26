#pragma once
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"
#include "JsoneResponsePacketSerializer.h"
class Game;
class GameRequestHandler :
	public IRequestHandler
{
public:
	GameRequestHandler();
	GameRequestHandler(LoggedUser* user, Game* game, GameManager* gameManager, RequestHandlerFactory* factory);
	bool isRequestRelevant(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	Game* m_game;
	LoggedUser* m_user;
	GameManager* m_gameManager;
	RequestHandlerFactory* m_handlerFactory;

	RequestResult getQuestion(Request r);
	RequestResult submitAnswer(Request r);
	RequestResult getGameResults(Request r);
	RequestResult leaveGame(Request r);
};

