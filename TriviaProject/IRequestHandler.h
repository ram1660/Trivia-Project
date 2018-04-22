#pragma once
#include <vector>

class IRequestHandler
{
public:
	virtual bool isRequestRelavent(Request r) = 0;
	virtual RequestResult handleRequest(Request r) = 0;
};

struct RequestResult
{
	Buffer response;
	IRequestHandler newHandler;
};
struct Request
{
	RequestId id;
	receivalTime ctime;
	std::vector<unsigned char> buffer;
};