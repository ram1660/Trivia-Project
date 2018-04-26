#pragma once
#include <vector>
#include "Structs.h"
class IRequestHandler
{
public:
	virtual bool isRequestRelavent(Request r) = 0;
	virtual RequestResult handleRequest(Request r) = 0;
};

