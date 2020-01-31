#pragma once
#include "structures.h"
#include <string>
#include "json.hpp"
using nlohmann::json;

class JsonResponsePacketSerializer
{
public:
	static std::vector<char> serializeResponse(ErrorResponse);
	static std::vector<char> serializeResponse(LoginResponse);
	static std::vector<char> serializeResponse(SignupResponse);
	static std::vector<char> serializeResponse(KeepAliveRequest);
	static std::vector<char> serializeResponse(GeneralResponse);
	//static std::vector<char> serializeResponse(LogoutResponse);
	static std::vector<char> serializeResponse(GetRoomsResponse);
	static std::vector<char> serializeResponse(GetPlayersInRoomResponse);
	static std::vector<char> serializeResponse(JoinRoomResponse);
	static std::vector<char> serializeResponse(CreateRoomResponse);
	static std::vector<char> serializeResponse(HighscoreResponse);
	static std::vector<char> serializeResponse(CloseRoomResponse);
	static std::vector<char> serializeResponse(StartRoomResponse);
	static std::vector<char> serializeResponse(GetRoomStateResponse);
	static std::vector<char> serializeResponse(LeaveRoomResponse);
};
