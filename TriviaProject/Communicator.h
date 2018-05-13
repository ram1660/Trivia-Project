#pragma once
#include <iostream>
#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <Windows.h>
#include <map>
#include <thread>
#include <mutex>
#include <deque>
#include <condition_variable>
#include "Buffer.h"
#include "JsoneResponsePacketSerializer.h"
#include "JsonRequestPacketDeserializer.h"
#include "LoginRequestHandler.h"
class IRequestHandler;
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
	void startThreadForNewClient();
	int getCode(SOCKET sc);
	char* getPartFromSocket(SOCKET sc, int bytesNumber);
	char* getPartFromSocket(SOCKET sc, int bytesNum, int flags);
	string getStringPartFromSocket(SOCKET sc, int bytesNum);
	string getPaddedNumber(int num, int digits);
	void sendData(SOCKET sc, Buffer message);
	void clientHandler(SOCKET clientSocket);
	int getLengthData(SOCKET clientSocket);
	std::map<SOCKET, IRequestHandler*> m_clients; // Shared resource
	RequestHandlerFactory m_handlerFactory;
	SOCKET _serverSocket;
	std::deque<std::pair<SOCKET, Request>> m_messageQ; // Shared resource
};