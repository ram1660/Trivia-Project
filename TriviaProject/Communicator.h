#pragma once
#include "JsoneResponsePacketSerializer.h"
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <thread>
#include "IDatabase.h"
#include "IRequestHandler.h"
#include <mutex>
#include <condition_variable>
#include "RequestHandlerFactory.h"
class Communicator
{
public:
	void bindAndListen();
	void handleRequests();
	Communicator();
	~Communicator();

private:
	void startThreadForNewClient();
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory m_handlerFactory;
	SOCKET _serverSocket;
};

