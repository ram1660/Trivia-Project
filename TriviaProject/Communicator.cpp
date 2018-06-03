#include "Communicator.h"
mutex mRequests, mClients;
condition_variable c;
static const unsigned short PORT = 7080;
static const unsigned int IFACE = 0;
Communicator::Communicator()
{
	_serverSocket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (_serverSocket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__ " - socket");
}

Communicator::~Communicator()
{
	for (int i = 0; i < m_clients.size(); i++)
		delete m_clients[i];

	try
	{
		::closesocket(_serverSocket);
	}
	catch (...) {}
}
void Communicator::bindAndListen()
{
	struct sockaddr_in sa = { 0 };
	std::cout << "Binding!" << std::endl;
	sa.sin_port = htons(PORT);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	if (::bind(_serverSocket, (struct sockaddr*)&sa, sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");
	if (::listen(_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << PORT << std::endl;
}
void Communicator::handleRequests()
{
	Request currentReq;
	unique_lock<mutex> requestsLocker(mRequests);
	//requestsLocker.unlock();
	while (true)
	{
		if (m_messageQ.empty())
			c.wait(requestsLocker);

		IRequestHandler* rq = m_clients.at(m_messageQ.front().first);
		currentReq = m_messageQ.front().second;
		SOCKET client = m_messageQ.front().first;
		if (rq->isRequestRelevant(currentReq))
		{
			RequestResult result = rq->handleRequest(currentReq);
			if (result.newHandler != nullptr)
				rq = result.newHandler;
			sendData(client, result.response);
		}
		else
		{
			ErrorResponse response;
			// Inform a new protocol.
			response.message = RESPONSE_ERROR;
			Buffer b;
			b.buffer = JsonResponsePacketSerializer::serializeResponse(response);
			sendData(client, b);
		}
		requestsLocker.lock();
		m_messageQ.pop_front();
		requestsLocker.unlock();
	}
}

void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	cout << "New client has been conected!" << endl;
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	unique_lock<mutex> usersLocker(mClients);
	m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, m_handlerFactory.createLoginRequestHandler()));
	usersLocker.unlock();
	std::thread t(&Communicator::clientHandler, this, client_socket);
	t.detach();
}

void Communicator::serve()
{
	bindAndListen();
	std::thread tr(&Communicator::handleRequests, this);
	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		startThreadForNewClient();
	}
}

void Communicator::clientHandler(SOCKET clientSocket)
{
	try
	{
		Request currRequest;
		vector<int> info = getInfoFromClient(clientSocket);
		int idRequest = info[0];
		currRequest.id = idRequest;
		int bufferLen = info[1];
		char *bufferData = getPartFromSocket(clientSocket, bufferLen);
		for (int i = 0; i < bufferLen; i++)
		{
			currRequest.buffer.push_back(bufferData[i]);
		}

		unique_lock<mutex> requestsLocker(mRequests);
		m_messageQ.push_back(make_pair(clientSocket, currRequest));
		requestsLocker.unlock();
		c.notify_all();
	}
	catch (const std::exception&)
	{
		closesocket(clientSocket);
	}
}

void Communicator::sendData(SOCKET sc, Buffer message)
{
	string strMessage;
	for (int i = 0; i < message.buffer.size(); i++)
		strMessage[i] += message.buffer[i];
	const char* data = strMessage.c_str();
	int size = static_cast<int>(message.buffer.size());
	if (send(sc, data, size, 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}

#pragma region Extracting data from client section
vector<int> Communicator::getInfoFromClient(SOCKET client)
{
	vector<int> info;
	char* buffInfo = getPartFromSocket(client, 5);
	int code = (int)buffInfo[0], size = 0;
	for (int i = 1; i < 5; i++) size |= (unsigned char)buffInfo[i] << (24 - (i - 1) * 8);
	info.push_back(code);
	info.push_back(size);
	return info;
}
vector<char> Communicator::getDataFromClient(SOCKET client, int size)
{
	vector<char> data;
	if (size)
	{
		char* bufferData = getPartFromSocket(client, size);
		for (int i = 0; i < size; i++) data.push_back(bufferData[i]);
		delete[] bufferData;
	}
	return data;
}

char * Communicator::getPartFromSocket(SOCKET sc, int bytesNumber)
{
	return getPartFromSocket(sc, bytesNumber, 0);
}

char * Communicator::getPartFromSocket(SOCKET sc, int bytesNum, int flags)
{
	if (bytesNum == 0)
		return 0;

	char* data = new char[bytesNum + 1];
	int res = recv(sc, data, bytesNum + 2, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while recieving from socket: ";
		s += std::to_string(sc);
		throw std::exception(s.c_str());
	}
	return data;
}
#pragma endregion