#pragma once
class IRequestHandler
{
public:
	bool isRequestRelavent(Request r);
	RequestResult handleRequest(Request r);

private:

};
