#include "LoginRequestHandler.h"
RequestResult LoginRequestHandler::handleRequest(Request r)
{
	Buffer b;
	b.buffer = r.buffer;
	LoginRequest request =  JsonRequestPacketDeserializer::deserializeLoginRequest(b);
	if (r.id == REQUEST_SIGNIN)
		return login(r);
	else if (r.id == REQUEST_SIGNUP)
		signup(r);
}

RequestResult LoginRequestHandler::login(Request r)
{
	// Calls to the DB.
	// Informing RequestResult struct and return it
	RequestResult result;
	result.
	return RequestResult();
}

RequestResult LoginRequestHandler::signup(Request r)
{
	// Calls to the DB.
	// Informing RequestResult struct and return it
	return RequestResult();
}

LoginRequestHandler::LoginRequestHandler(LoginManager & manager, RequestHandlerFactory factory) : m_loginManager(&manager), m_handlerFactory(&factory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
	delete m_loginManager;
	delete m_handlerFactory;
}

bool LoginRequestHandler::isRequestRelavent(Request r)
{
	if (r.id == REQUEST_SIGNUP || r.id == REQUEST_SIGNIN)
		return true;
	return false;
}
