#pragma once
#include <iostream>
#include <map>
#include <vector>
#include <bitset>
#include <cstddef>
#include "Buffer.h"
class HighscoreTable;
class IRequestHandler;
class Question;
using namespace std;

struct RoomData
{
	unsigned int id;
	string name;
	string maxPlayers;
	unsigned int timePerQuestion;
	unsigned int isActive;
};


		/*HANDLERS*/
struct RequestResult
{
	Buffer* response;
	IRequestHandler* newHandler;
};

struct Request
{
	unsigned int id;
	time_t receivalTime;
	vector<char*> buffer;
};

		/*RESPONSE*/
struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct LogoutResponse
{
	unsigned int status;
};

struct getRoomsResponse
{
	unsigned int status;
	vector<RoomData*> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> rooms;
};

struct HighscoreResponse
{
	unsigned int status;
	vector<HighscoreTable> Highscores;

};

struct JoinRoomResponse
{
	unsigned int status;
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
	unsigned int answerTimeout; /////////////////////////////////
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

		
	
		/*MANAGERS*/
struct GameData
{
	Question* currentQuestion;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
};
