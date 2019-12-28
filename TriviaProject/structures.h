#pragma once
#include <iostream>
#include <map>
#include <bitset>
#include <cstddef>
#include "Buffer.h"

#define ROOM_STATUS_WAITING 0
#define ROOM_STATUS_IN_A_PROGRESS 1
#define DEFAULT_QUESTION_COUNT 10
class HighscoreTable;
class IRequestHandler;
class Question;
using namespace std;

struct RoomData
{
	string name;
	unsigned int id = 0;
	unsigned int maxPlayers = 0;
	unsigned int timePerQuestion = 0;
	unsigned int isActive = 0;
	unsigned int questionCount = 0;
};


		/*HANDLERS*/
struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};

struct Request
{
	unsigned int id = 0;
	time_t receivalTime;
	vector<char> buffer;
};

		/*RESPONSE*/
struct LoginResponse
{
	unsigned int status = 0;
};

struct SignupResponse
{
	unsigned int status = 0;
};

struct LogoutResponse
{
	unsigned int status = 0;
};

struct GetRoomsResponse
{
	unsigned int status = 0;
	vector<RoomData*> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> rooms;
};

struct HighscoreResponse
{
	unsigned int status = 0;
	//vector<HighscoreTable> highscores;
};

struct JoinRoomResponse
{
	unsigned int status = 0;
};

struct CreateRoomResponse
{
	unsigned int status;
};

struct CloseRoomResponse
{
	unsigned int status;
};

struct StartRoomResponse
{
	unsigned int status;
};

struct GetRoomStateResponse
{
	unsigned int status;
	bool hasGameBegun;
	vector<string> players;
	unsigned int questionCount;
	unsigned int answerTimeout; 
};

struct LeaveRoomResponse
{
	unsigned int status;
}; 

struct GetQuestionResponse
{
	unsigned int status;
	string question;
	map<unsigned int, string> anwers;
};

struct SubmitAnswerResponse
{
	unsigned int status;
	unsigned int correctAnswerId;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};

struct GetGameResultResponse
{
	unsigned int status;
	vector<PlayerResults*> results;
};

struct ErrorResponse
{
	std::string message;
};

struct KeepAliveResponse
{
	int code;
};

		/*REQUEST*/
struct LoginRequest
{
	string username;
	string password;
};
struct SignupRequest
{
	string username;
	string password;
	string email;
};
struct CreateRoomRequest
{
	string username;
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId;
};

struct JoinRoomRequest
{
	string username;
	unsigned int roomId;
};

struct SignoutRequest
{
	string username;
};

struct KeepAliveRequest
{
	unsigned int code;
};

struct GeneralResponse
{
	unsigned int code;
};
	
		/*MANAGERS*/
struct GameData
{
	Question* currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};
