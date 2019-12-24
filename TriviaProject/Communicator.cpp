#include "Communicator.h"
mutex mClients;
recursive_mutex mRequests;
condition_variable cClients;
condition_variable_any cRequests;
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
	unique_lock<recursive_mutex> requestsLocker1(mRequests);
	while (true)
	{
		if (m_messageQ.empty())
			cRequests.wait(requestsLocker1);
		if (m_messageQ.front().second.id != RESPONSE_KEEP_ALIVE)
		{
			IRequestHandler* rq = m_clients.at(m_messageQ.front().first);
			currentReq = m_messageQ.front().second;

			SOCKET client = m_messageQ.front().first;
			if (rq->isRequestRelevant(currentReq))
			{
				RequestResult result = rq->handleRequest(currentReq);
				if (result.newHandler != nullptr)
					rq = result.newHandler;
				try
				{
					sendData(client, result.response);
				}
				catch (const std::exception& e)
				{
					cout << "What=" << e.what() << endl;
				}
			}
			else
			{
				ErrorResponse response;
				response.message = RESPONSE_ERROR;
				Buffer b;
				b.buffer = JsonResponsePacketSerializer::serializeResponse(response);
				try
				{
					sendData(client, b);

				}
				catch (const std::exception& e)
				{
					cout << "What=" << e.what() << endl;
				}
			}
			//requestsLocker1.try_lock();
			m_messageQ.pop_front();
		}
		else
		{
			m_keepAliveMap.insert(m_messageQ.front());
			m_messageQ.pop_front();
		}
		//requestsLocker1.unlock();
	}
}

void Communicator::keepAlive()
{
	KeepAliveRequest keepRequest;
	Request request;
	map<SOCKET, IRequestHandler*>::iterator itMap;
	//map<SOCKET, Request> keepAliveDeque;
	bool isClientsEmpty = false;
	//deque<pair<SOCKET, Request>>::iterator itDeque;
	bool firstMessageHasSent = false;
	while (true)
	{
		for (itMap = m_clients.begin(); itMap != m_clients.end(); itMap++)
		{
			keepRequest.code = REQUEST_KEEP_ALIVE;
			Buffer data;
			vector<char> jsonRequest = JsonResponsePacketSerializer::serializeResponse(keepRequest);
			data.buffer.push_back(REQUEST_KEEP_ALIVE);
			data.buffer.insert(data.buffer.end(), jsonRequest.begin(), jsonRequest.end());
			firstMessageHasSent = true;
			cout << "Sending keep alive request to " << itMap->first << endl;
			try
			{
				sendData(itMap->first, data);
			}
			catch (const std::exception& e)
			{
				cout << "What=" << e.what() << endl;
			}
		}
		this_thread::sleep_for(chrono::seconds(15));

		for (size_t i = 0; i < m_messageQ.size(); i++)
			if (m_messageQ[i].second.id == RESPONSE_KEEP_ALIVE)
			{
				m_keepAliveMap.insert(make_pair(m_messageQ[i].first, m_messageQ[i].second));
				m_messageQ.erase(m_messageQ.begin() + i);
			}
		if (!m_clients.empty())
		{
			for (itMap = m_clients.begin(); itMap != m_clients.end(); itMap++)
			{
				for (size_t i = 0; i < m_keepAliveMap.size(); i++)
				{
					if (m_keepAliveMap.find(itMap->first) == m_keepAliveMap.end())
					{
						cout << "A client lost connection with: " << m_keepAliveMap.find(itMap->first)->first << "!" << endl;
						m_clients.erase(m_clients.find((m_keepAliveMap.find(itMap->first))->first));
						if (m_clients.size() == 0)
							isClientsEmpty = true;
					}
					else
						cout << "The client " << itMap->first << " is still alive!" << endl;
				}
				if (isClientsEmpty)
					break;
			}
			isClientsEmpty = false;
			if (firstMessageHasSent && m_clients.size() == 1 && m_keepAliveMap.size() == 0)
			{
				cout << "A client lost connection with: " << m_clients.begin()->first << "!" << endl;
				m_clients.erase(m_clients.begin());
				firstMessageHasSent = false;
			}
		}
		m_keepAliveMap.clear();
	}
}
void Communicator::startThreadForNewClient()
{
	SOCKET client_socket = ::accept(_serverSocket, NULL, NULL);
	cout << "New client has been conected!" << endl;
	if (client_socket == INVALID_SOCKET)
		throw std::exception(__FUNCTION__);
	{
		lock_guard<mutex> usersLocker(mClients);
		m_clients.insert(pair<SOCKET, IRequestHandler*>(client_socket, m_handlerFactory.createLoginRequestHandler()));
	}
	std::thread t(&Communicator::clientHandler, this, client_socket);
	t.detach();
}

void Communicator::serve()
{
	bindAndListen();
	std::thread tr(&Communicator::handleRequests, this);
	std::thread keepAliveThread(&Communicator::keepAlive, this);
	keepAliveThread.detach();
	tr.detach();
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
		//;
		while (true)
		{
			Request currRequest;
			try
			{
				if (m_clients.find(clientSocket) != m_clients.end())
					currRequest = getInfoFromClient(clientSocket);
				else
					break;
			}
			catch (const std::exception& e)
			{
				std::cout << "Exception was catch in function clientHandler. socket=" << clientSocket << ", what=" << e.what() << std::endl;
				break;
			}
			{
				//unique_lock<recursive_mutex> requestsLocker2(mRequests, std::defer_lock);
				//requestsLocker2.lock();
					m_messageQ.push_back(make_pair(clientSocket, currRequest));
				//requestsLocker2.unlock();
			}
			//requestsLocker2.lock();
			if(currRequest.id != RESPONSE_KEEP_ALIVE)
				cRequests.notify_all();
		}
	}
	catch (const std::exception& e)
	{
		cout << "Something went wrong! " << e.what() << endl;
	}
}

void Communicator::sendData(SOCKET sc, Buffer message)
{
	vector<char> buff;
	buff.push_back(message.buffer[0]);
	message.buffer.erase(message.buffer.begin());
	string strMessage{ (message.buffer).begin(), (message.buffer).end() };
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
	//delete[] data;
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