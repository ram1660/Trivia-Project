#include "Server.h"
#include "WSAInitializer.h"
#include <vld.h>
#include <exception>
int main()
{
	try
	{
		WSAInitializer wsa;
		Server server;
		server.run();
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
}