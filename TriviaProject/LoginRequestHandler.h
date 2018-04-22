#pragma once
#include "IRequestHandler.h"
class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestRelevan(Request r);
	RequestResult handleRequest(Request r);
	virtual bool isRequestRelavent(Request r) override;
	virtual RequestResult handleRequest(Request r) override;
private:
	LoginManager m_loginManager;
	RequestHandlerFactory m_handlerFactory;
	RequestResult login(Request r);
	RequestResult signup(Request r);
};