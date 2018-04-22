#pragma once
#include "LoginRequestHandler.h"
class RequestHnadlerFactory
{
public:
	LoginRequestHandler createLoginRequestHandler();
private:
	LoginManager m_loginManager;
};

