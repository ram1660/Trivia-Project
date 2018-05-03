#include "Communicator.h"
#define PORT 5023
mutex m;
condition_variable c;
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

	while (true)
	{
		std::cout << "Waiting for client connection request" << std::endl;
		startThreadForNewClient();
	}
}

void Communicator::handleRequests(SOCKET& client)
{
	Request currentReq;
	while (true)
	{	
		int idRequest = getCode(client);
		int bufferLen = atoi(getPartFromSocket(client, 2));
		char *bufferData = getPartFromSocket(client, bufferLen);
		for (int i = 0; i < 5; i++)
		{
			currentReq.buffer.push_back(bufferData[i]);
		}
		IRequestHandler* rq = m_clients.at(client);
		if (rq->isRequestRelavent(currentReq))
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
	}
}

void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, m_handlerFactory.createLoginRequestHandler()));

	thread t(&Communicator::handleRequests, ref(client_socket), client_socket);
	t.detach();

}

int Communicator::getCode(SOCKET sc)
{
	char* s = getPartFromSocket(sc, 1);
	string msg(s);

	if (msg == "")
		return 0;

	int res = std::atoi(s);
	delete s;
	return  res;
	return 0;
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
	int res = recv(sc, data, bytesNum, flags);

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
	//string test = message.buffer[10] + message.buffer[1];
	const char* data = message.buffer; // Ask how the sending works.

	if (send(sc, data, message.buffer.size(), 0) == INVALID_SOCKET)
		throw std::exception("Error while sending message to client");
}
