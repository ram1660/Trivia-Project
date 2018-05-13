#include "Communicator.h"
mutex m;
condition_variable c;
static const unsigned short PORT = 8080;
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
	while (true)
	{
		unique_lock<mutex> requestsLocker(m);
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
			Buffer b = JsonResponsePacketSerializer::serializeResponse(response);
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
	unique_lock<mutex> usersLocker(m);
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
		int idRequest = getCode(clientSocket);
		currRequest.id = idRequest;
		int bufferLen = getLengthData(clientSocket);
		char *bufferData = getPartFromSocket(clientSocket, bufferLen);
		for (int i = 0; i < 5; i++)
		{
			currRequest.buffer.push_back(bufferData[i]);
		}
		unique_lock<mutex> requestsLocker(m);
		m_messageQ.push_back(make_pair(clientSocket, currRequest));
		requestsLocker.unlock();
		c.notify_all();
	}
	catch (const std::exception& e)
	{
		closesocket(clientSocket);
	}
}

int Communicator::getLengthData(SOCKET clientSocket)
{
	char* len = getPartFromSocket(clientSocket, 4);
	int size = 0;
	
	for (int i = 0; i < 4; i++)
	{
		cout << (int)len[i] << endl;
		//size |= (unsigned char)len[i] << (24 - (i - 1) * 8);
	}
	int x = strtol(len, nullptr, 0);
	return x;
}


int Communicator::getCode(SOCKET sc)
{
	char* s = getPartFromSocket(sc, 1);
	int res = *s;
	return  res;
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

	data[bytesNum] = 0;
	return data;
	return nullptr;
}

string Communicator::getStringPartFromSocket(SOCKET sc, int bytesNum)
{
	char* s = getPartFromSocket(sc, bytesNum, 0);
	string res(s);
	return res;
}

string Communicator::getPaddedNumber(int num, int digits)
{
	std::ostringstream ostr;
	ostr << std::setw(digits) << std::setfill('0') << num;
	return ostr.str();
}

void Communicator::sendData(SOCKET sc, Buffer message)
{
	string strMessage;
	for (int i = 0; i < message.buffer.size(); i++)
		strMessage[i] += message.buffer[i];
	const char* data = strMessage.c_str();

	if (send(sc, data, message.buffer.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}