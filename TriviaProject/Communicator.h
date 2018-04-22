#pragma once
#include "JsoneResponsePacketSerializer.h"
#include <WinSock2.h>
#include <Windows.h>
#include <deque>
#include <map>
#include <thread>
#include "IDatabase.h"
class Communicator
{
public:
	void bindAndListen();
	void handeRequests();
private:
	void startThreadForNewClient();
	std::map<SOCKET, IRequestHandlerFactory> m_clients;
};

