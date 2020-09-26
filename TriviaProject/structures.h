#pragma once
#include <iostream>
#include <map>
#include <bitset>
#include <cstddef>
#include "Question.h"
#include "Buffer.h"
#define ROOM_STATUS_WAITING 0
#define ROOM_STATUS_IN_A_PROGRESS 1
#define DEFAULT_QUESTION_COUNT 10
class HighscoreTable;
class IRequestHandler;
class Question;
class LoggedUser;
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

struct GameData
{
	Question* currentQuestion;
	unsigned int correctAnswerCount = 0;
	unsigned int wrongAnswerCount = 0;
	unsigned int averageAnswerTime = 0;
	unsigned int currentQuestionIndex = 0;
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
	map<string, unsigned int> highscores;
};

struct JoinRoomResponse
{
	unsigned int status = 0;
};

struct CreateRoomResponse
{
	unsigned int status = 0;
};

struct CloseRoomResponse
{
	unsigned int status = 0;
};

struct StartRoomResponse
{
	unsigned int status = 0;
};

struct GetRoomStateResponse
{
	unsigned int status = 0;
	bool hasGameBegun = false;
	vector<string> players;
	unsigned int questionCount = 0;
	unsigned int answerTimeout = 0; 
};

struct LeaveRoomResponse
{
	unsigned int status;
}; 

struct ErrorResponse
{
	std::string message;
};

struct KeepAliveResponse
{
	int code = 0;
};

struct GetQuestionResponse
{
	unsigned int status = 0;
	std::string question;
	std::map<unsigned int, std::string> answers;
};

struct SubmitAnswerResponse
{
	unsigned int status = 0;
	unsigned int correctAnswer = 0;
};

struct PlayerResults
{
	std::string username;
	unsigned int correctAnswerCount = 0;
	unsigned int wrongAnswerCount = 0;
	unsigned int averageAnswerTime = 0;
};

struct GetGameResultsResponse
{
	unsigned int status = 0;
	std::vector<PlayerResults> results;
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
	unsigned int maxUsers = 0;
	unsigned int questionCount = 0;
	unsigned int answerTimeout = 0;
};

struct GetPlayersInRoomRequest
{
	unsigned int roomId = -999;
};

struct JoinRoomRequest
{
	string username;
	unsigned int roomId = -999;
};

struct SignoutRequest
{
	string username;
};

struct KeepAliveRequest
{
	unsigned int code = 0;
};

struct GeneralResponse
{
	unsigned int code = 0;
};
	
struct SubmitAnswerRequest
{
	unsigned int answerId = -999;
};

struct GetGameResultsRequest
{
	unsigned int roodId = -999;
};

		/*MANAGERS*/
//struct GameData
//{
//	Question* currentQuestion;
//	unsigned int correctAnswerCount;
//	unsigned int wrongAnswerCount;
//	unsigned int averageAnswerTime;
//};
