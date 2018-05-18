#include "LoginRequestHandler.h"
LoginRequestHandler::LoginRequestHandler()
{
}
LoginRequestHandler::LoginRequestHandler(LoginManager* manager, RequestHandlerFactory* factory) : m_loginManager(manager), m_handlerFactory(factory)
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
	return RequestResult();
}

RequestResult LoginRequestHandler::login(Request r)
{
	// Calls to the DB with loginManager.
	// Informing RequestResult struct and return it
	Buffer b;
	b.buffer = r.buffer;
	LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(b);
	RequestResult result;
	
	
	
	if (m_loginManager->login(request.username, request.password))
	{
		LoginResponse login;
		login.status = RESPONSE_SIGNIN;
		Buffer b =JsonResponsePacketSerializer::serializeResponse(login);
		result.response = b;
		result.newHandler = m_handlerFactory->createMenuRequestHandler();
	}
	else
	{
		ErrorResponse error;
		error.message = "ERROR: This user doesn't exists!";
		Buffer b = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::signup(Request r)
{
	// Calls to the DB.
	// Informing RequestResult struct and return it
	Buffer b;
	b.buffer = r.buffer;
	SignupRequest request = JsonRequestPacketDeserializer::deserializeSignupRequest(b);
	RequestResult result;
	
	if (!(m_loginManager->signup(request.username, request.password, request.email)))
	{
		ErrorResponse error;
		error.message = "ERROR: This user already exists!";
		Buffer b = JsonResponsePacketSerializer::serializeResponse(error);
		result.response = b;
		result.newHandler = nullptr;
	}
	else
	{
		SignupResponse response;
		response.status = RESPONSE_SIGNUP;
		Buffer b = JsonResponsePacketSerializer::serializeResponse(response);
		result.newHandler = new LoginRequestHandler(m_loginManager, m_handlerFactory);
	}
	return result;
}

bool LoginRequestHandler::isRequestRelevant(Request r)
{
	if (r.id == REQUEST_SIGNUP || r.id == REQUEST_SIGNIN)
		return true;
	return false;
}
