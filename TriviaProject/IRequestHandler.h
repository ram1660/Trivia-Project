#pragma once
#include <vector>
#include "Buffer.h"

struct RequestResult
{
	Buffer response;
	IRequestHandler& newHandler;
};

struct Request
{
	unsigned int id;
	time_t receivalTime;
	Buffer buffer;
};
class IRequestHandler
{
public:
	IRequestHandler();
	~IRequestHandler();
	virtual bool isRequestRelavent(Request r) = 0;
	virtual RequestResult handleRequest(Request r) = 0;
};

