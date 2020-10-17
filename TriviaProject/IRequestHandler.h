#pragma once
#include "structures.h"
class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const Request& r) = 0;
	virtual RequestResult handleRequest(Request r) = 0;
};

