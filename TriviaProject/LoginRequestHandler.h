#pragma once
#include <algorithm>
#include "IRequestHandler.h"
#include "structures.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "JsoneResponsePacketSerializer.h"
#include "Protocol.h"
class LoginManager;
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler();
	LoginRequestHandler(LoginManager* manager, RequestHandlerFactory* factory);
	~LoginRequestHandler();
	bool isRequestRelevant(const Request& r) override;
	RequestResult handleRequest(Request r) override;
private:
	RequestResult login(const Request& r);
	RequestResult signup(const Request& r);

	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handlerFactory;
};