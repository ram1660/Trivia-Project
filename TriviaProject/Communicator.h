#pragma once
#include <WinSock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")

#include <map>
#include <thread>
#include <mutex>

#include "IDatabase.h"
#include "IRequestHandler.h"
#include <condition_variable>
#include "Protocol.h"
#include "RequestHandlerFactory.h"

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
	std::map<SOCKET, IRequestHandler*> m_clients;
	RequestHandlerFactory m_handlerFactory;
	SOCKET _serverSocket;
};