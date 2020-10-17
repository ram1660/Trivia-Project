#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <thread>
#include <mutex>
#include <stdlib.h>
#include <stdio.h>
#include <deque>
#include <condition_variable>
#include "LoginRequestHandler.h"
class IRequestHandler;
class HighscoreTable;
class RequestHandlerFactory;
class Communicator
{
public:
	void bindAndListen();
	void handleRequests();
	void serve();
	Communicator();
	~Communicator();

private:
	void keepAlive(); // Making sure that the server has connections to all the clients.
	void startThreadForNewClient();
	vector<char> getDataFromClient(SOCKET client, int size);
	char* getPartFromSocket(SOCKET sc, int bytesNumber);
	char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	Request getInfoFromClient(SOCKET client);
	void sendData(SOCKET sc, Buffer& message);
	void clientHandler(SOCKET clientSocket);

	//FIELDS
	std::map<SOCKET, IRequestHandler*> m_clients; // Shared resource
	RequestHandlerFactory m_handlerFactory;
	SOCKET _serverSocket;
	std::deque<std::pair<SOCKET, Request>> m_messageQ; // Shared resource
	std::map<SOCKET, Request> m_keepAliveMap;
};