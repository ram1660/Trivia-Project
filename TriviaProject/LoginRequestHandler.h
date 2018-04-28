#pragma once
#include "IRequestHandler.h"
#include "structures.h"
#include "RequestHandlerFactory.h"
class LoginRequestHandler : public IRequestHandler
{
public:
	~LoginRequestHandler();
	bool isRequestRelavent(Request r) override;
	RequestResult handleRequest(Request r) override;
private:
	LoginManager* m_loginManager;
	RequestHandlerFactory* m_handlerFactory;
	RequestResult login(Request r);
	RequestResult signup(Request r);
};