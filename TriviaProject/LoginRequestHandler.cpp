#include "LoginRequestHandler.h"
LoginRequestHandler::LoginRequestHandler() : m_loginManager(new LoginManager()), m_handlerFactory(new RequestHandlerFactory())
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
	if (r.id == REQUEST_SIGNIN)
		return login(r);
	else
		return signup(r);
}

RequestResult LoginRequestHandler::login(const Request& r)
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
		Buffer finalBuffer;
		vector<char> code, data;
		code.push_back(RESPONSE_SIGNIN);
		data = JsonResponsePacketSerializer::serializeResponse(login);
		finalBuffer.buffer.reserve(code.size() + data.size());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), code.begin(), code.end());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), data.begin(), data.end());
		result.response = finalBuffer;
		result.newHandler = m_handlerFactory->createMenuRequestHandler();
	}
	else
	{
		ErrorResponse error;
		error.message = "ERROR: This user doesn't exists!";
		Buffer finalBuffer;
		vector<char> code, data;
		code.push_back(RESPONSE_ERROR);
		data = JsonResponsePacketSerializer::serializeResponse(error);
		finalBuffer.buffer.reserve(code.size() + data.size());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), code.begin(), code.end());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), data.begin(), data.end());
		result.response = finalBuffer;
		result.newHandler = nullptr;
	}
	return result;
}

RequestResult LoginRequestHandler::signup(const Request& r)
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
		Buffer finalBuffer;
		vector<char> code, data;
		code.push_back(RESPONSE_ERROR);
		data = JsonResponsePacketSerializer::serializeResponse(error);
		finalBuffer.buffer.reserve(code.size() + data.size());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), code.begin(), code.end());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), data.begin(), data.end());
		result.response = finalBuffer;
		result.newHandler = nullptr;
	}
	else
	{
		SignupResponse response;
		response.status = RESPONSE_SIGNUP;
		Buffer finalBuffer;
		vector<char> code, data;
		code.push_back(RESPONSE_SIGNUP);
		data = JsonResponsePacketSerializer::serializeResponse(response);
		finalBuffer.buffer.reserve(code.size() + data.size());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), code.begin(), code.end());
		finalBuffer.buffer.insert(finalBuffer.buffer.end(), data.begin(), data.end());
		result.response = finalBuffer;
		result.newHandler = new LoginRequestHandler(m_loginManager, m_handlerFactory);
	}
	return result;
}


bool LoginRequestHandler::isRequestRelevant(const Request& r)
{
	if (r.id == REQUEST_SIGNUP || r.id == REQUEST_SIGNIN)
		return true;
	return false;
}
