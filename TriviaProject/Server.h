#pragma once
#include "RequestHandlerFactory.h"
#include "Communicator.h"
class Server
{
public:
	Server();
	~Server();
	Server(IDatabase& db, Communicator communicator, RequestHandlerFactory factory);
	void run();
private:
	IDatabase* m_database;
	Communicator m_communicator;
	RequestHandlerFactory m_handlerFactory;
};

