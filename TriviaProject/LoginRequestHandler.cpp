#include "LoginRequestHandler.h"
#include "structures.h"
bool LoginRequestHandler::isRequestRelevan(Request r)
{
	
	return false;
}

RequestResult LoginRequestHandler::handleRequest(Request r)
{
	return RequestResult();
}

RequestResult LoginRequestHandler::login(Request r)
{
	return RequestResult();
}

RequestResult LoginRequestHandler::signup(Request r)
{
	return RequestResult();
}

LoginRequestHandler::~LoginRequestHandler()
{
}

bool LoginRequestHandler::isRequestRelavent(Request r)
{
	return false;
}