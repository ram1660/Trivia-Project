#include "Communicator.h"
#define PORT 5023
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
	while (true)
	{

	}
}

void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	m_clients.insert(pair<SOCKET, IRequestHandler>(client_socket, m_handlerFactory.createLoginRequestHandler()));

	thread t(&Communicator::handleRequests, this, client_socket);
	t.detach();

}
