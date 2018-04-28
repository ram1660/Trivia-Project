#pragma once
#include "LoginRequestHandler.h"
#include "Structs.h"
#include "LoginManager.h"
class RequestHandlerFactory
{
public:
	LoginRequestHandler createLoginRequestHandler();
private:
	LoginManager m_loginManager;
};

