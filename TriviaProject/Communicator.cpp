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

void Communicator::handleRequests()
{
	std::map<SOCKET, IRequestHandler*>::iterator it = m_clients.begin();
	SOCKET user_socket = it->first;
	vector<unsigned char> buffer;
	while (true)
	{
		int res = recv(user_socket, buffer, bytesNum, flags);
	}
}

void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, m_handlerFactory.createLoginRequestHandler()));

	thread t(&Communicator::handleRequests, this, client_socket);
	t.detach();

}
