#include "Server.h"

Server::Server()
{
}


Server::~Server()
{
	delete m_database;
}

Server::Server(IDatabase & db, Communicator communicator, RequestHandlerFactory factory) : m_database(&db), m_communicator(communicator), m_handlerFactory(factory)
{
}

void Server::run()
{
	//Communicator communicator();
	//m_communicator = 
	m_communicator.bindAndListen();
	
}
