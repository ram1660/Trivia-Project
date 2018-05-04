#pragma once
#include <vector>
#include "structures.h"
class IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequestRelevant(Request r) = 0;
	virtual RequestResult handleRequest(Request r) = 0;
};

