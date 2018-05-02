#include "LoginRequestHandler.h"
LoginRequestHandler::LoginRequestHandler(LoginManager & manager, RequestHandlerFactory factory) : m_loginManager(&manager), m_handlerFactory(&factory)
{
}

LoginRequestHandler::~LoginRequestHandler()
{
	delete m_loginManager;
	delete m_handlerFactory;
}

RequestResult LoginRequestHandler::handleRequest(Request r)
{
	Buffer b;
	b.buffer = r.buffer;
	LoginRequest request =  JsonRequestPacketDeserializer::deserializeLoginRequest(b);
	if (r.id == REQUEST_SIGNIN)
		return login(r);
	else if (r.id == REQUEST_SIGNUP)
		return signup(r);
}

RequestResult LoginRequestHandler::login(Request r)
{
	// Calls to the DB with loginManager.
	// Informing RequestResult struct and return it
	Buffer b;
	b = r.buffer;
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(b);
	RequestResult result;
	m_loginManager->login(request.username, request.password);
	return RequestResult();
}

RequestResult LoginRequestHandler::signup(Request r)
{
	// Calls to the DB.
	// Informing RequestResult struct and return it
	return RequestResult();
}

bool LoginRequestHandler::isRequestRelavent(Request r)
{
	if (r.id == REQUEST_SIGNUP || r.id == REQUEST_SIGNIN)
		return true;
	return false;
}
