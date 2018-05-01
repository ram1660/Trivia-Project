#pragma once
#include "IRequestHandler.h"
#include "structures.h"
#include "RequestHandlerFactory.h"
#include "JsonRequestPacketDeserializer.h"
#include "Protocol.h"
#include "structures.h"
class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(LoginManager& manager, RequestHandlerFactory factory);
	~LoginRequestHandler();
	bool isRequestRelavent(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult login(Request r);
	RequestResult signup(Request r);
};