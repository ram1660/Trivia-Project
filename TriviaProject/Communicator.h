#pragma once
#include "JsoneResponsePacketSerializer.h"
#include <WinSock2.h>
#include <Windows.h>
#include <deque>
#include <map>
#include <thread>
#include "IDatabase.h"
#include "i"
class Communicator
{
public:
	void bindAndListen();
	void handleRequests();
	Communicator();
	~Communicator();

private:
	void startThreadForNewClient();
	std::map<SOCKET, IRequestHandlerFactory> m_clients;
	SOCKET _serverSocket;
};

