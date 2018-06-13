#include "Communicator.h"
mutex mRequests, mClients;
condition_variable c;
static const unsigned short PORT = 7080;
static const unsigned int IFACE = 0;
Communicator::Communicator() : m_handlerFactory(new LoginManager(), new RoomManager(), new HighscoreTable())
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
	unique_lock<mutex> requestsLocker(mRequests, std::defer_lock);

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
		//requestsLocker.lock();
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
		unique_lock<mutex> requestsLocker(mRequests, std::defer_lock);
		while (true)
		{
			Request currRequest;
			try
			{
				currRequest = getInfoFromClient(clientSocket);
			}
			catch (const std::exception& e)
			{
				std::cout << "Exception was catch in function clientHandler. socket=" << clientSocket << ", what=" << e.what() << std::endl;
				break;
			}
			requestsLocker.lock();
			m_messageQ.push_back(make_pair(clientSocket, currRequest));
			requestsLocker.unlock();
			c.notify_all();
		}
	}
	catch (const std::exception& e)
	{
	}
}

void Communicator::sendData(SOCKET sc, Buffer message)
{
	string strMessage{ (message.buffer).begin(), (message.buffer).end() };
	vector<char> buff;
	for (int i = 0; i < 4; i++)
		buff.push_back(strMessage.length() >> ((3 - i) * 8));
	for (int i = 0; i < strMessage.size(); i++)
		buff.push_back(strMessage[i]);
	char* n = new char[buff.size()];
	for (int i = 0; i < buff.size(); i++)
		n[i] = buff[i];
	if (send(sc, n, buff.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}

#pragma region Extracting data from client section
Request Communicator::getInfoFromClient(SOCKET client)
{
	Request request;
	char* infoFromSocket = getPartFromSocket(client, 5);
	int code = (int)infoFromSocket[0], size = 0;
	for (int i = 1; i < 5; i++) size |= (unsigned char)infoFromSocket[i] << (24 - (i - 1) * 8);
	request.id = code;
	Buffer buff;
	buff.buffer.push_back('{');
	buff.buffer.push_back('\"');

	char* data = new char[size];
	data = getPartFromSocket(client, size);
	for (int i = 0; i < size; i++) buff.buffer.push_back(data[i]);
	buff.buffer.pop_back();
	buff.buffer.pop_back();
	delete[] data;
	request.buffer = buff.buffer;
	return request;
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