#include "RequestHandlerFactory.h"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	LoginRequestHandler* login;
	return login;
}

RequestHandlerFactory::~RequestHandlerFactory()
{
	delete m_loginManager;
}

RequestHandlerFactory::RequestHandlerFactory() : m_loginManager(nullptr)
{
}

RequestHandlerFactory::RequestHandlerFactory(LoginManager* manager) : m_loginManager(manager)
{
}
