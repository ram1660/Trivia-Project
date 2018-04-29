#include "Server.h"
#include <exception>
int main()
{
	try
	{
		Server server;
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}