#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>

#include <map>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
#include <iostream>

#include "Buffer.h"
//#include "IDatabase.h"
#include "IRequestHandler.h"
#include "Protocol.h"
#include "RequestHandlerFactory.h"
class Buffer;
class IRequestHandler;
class RequestHandlerFactory;
class Communicator
{
public:
	void bindAndListen();
	void handleRequests(SOCKET& client);
	Communicator();
	~Communicator();

private:
	void startThreadForNewClient();
	int getCode(SOCKET sc);
	char* getPartFromSocket(SOCKET sc, int bytesNumber);
	char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	string getStringPartFromSocket(SOCKET sc, int bytesNum);
	string getPaddedNumber(int num, int digits);
	void sendData(SOCKET sc, Buffer message);
	
	std::map<SOCKET, IRequestHandler*> m_clients; // Shared resource
	RequestHandlerFactory m_handlerFactory;
	SOCKET _serverSocket;
	std::deque<std::pair<SOCKET, Buffer>> m_meesageQ; // Shared resource
};