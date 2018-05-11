#pragma once
#include "IRequestHandler.h"
#include "structures.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsoneResponsePacketSerializer.h"
#include "Protocol.h"
class LoginManager;
class RequestHandlerFactory;
#include <algorithm>

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager* manager, RequestHandlerFactory* factory);
	~LoginRequestHandler();
	bool isRequestRelevant(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult login(Request r);
	RequestResult signup(Request r);
};