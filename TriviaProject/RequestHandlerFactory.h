#pragma once
#include "LoginRequestHandler.h"
#include "structures.h"
#include "LoginManager.h"
class RequestHandlerFactory
{
public:
	LoginRequestHandler* createLoginRequestHandler();
	~RequestHandlerFactory();
	RequestHandlerFactory();
	RequestHandlerFactory(LoginManager* manager);

private:
	LoginManager* m_loginManager;
};

