#include <iostream>
#include <map>
#include <vector>
#include <time.h>
#include <ctime>
using namespace std;




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
	vector<RoomData> rooms;
};

struct GetPlayersInRoomResponse
{
	vector<string> rooms;
};

struct HighscoreResponse
{
	unsigned int status;
	vector<Highscore> Highscores;

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

struct GetGameResultResponse
{
	unsigned int status;
	vector<PlayerResults> results;
};

struct ErrorResponse
{
	std::string message;
};

struct PlayerResults
{
	string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	unsigned int averageAnswerTime;
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

struct GetPlayersInRoomRequest
{
	unsigned int roomId;	
};

struct JoinRoomRequest
{
	unsigned int roomId;
};

struct CreateRoomRequest
{
	string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
};

struct SubmitAnswerRequest
{
	unsigned int answerId;
};

		/*HANDLERS*/
struct RequestResult
{
	Buffer response;
	IRequestHandler* newHandler;
};
struct Request
{
	RequestId id;
	ctime receivalTime;
	vector<Byte> buffer;
};
class IRequestHandler
{
public: 
	virtual bool isRequestRelevant(Request) = 0;
	virtual RequestResult handleRequest(Request) = 0;

};