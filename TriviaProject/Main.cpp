#include "Server.h"
#include <exception>
int main()
{
	try
	{
		Server server;
		server.run();
	}
	catch (const std::exception&)
	{

	}
}