#include "JsoneResponsePacketSerializer.h"
using nlohmann::json;
std::vector<char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse e)
{
	json j;
	j["message"] = e.message;		
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LoginResponse l)
{
	json j;
	j["status"] = l.status;
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SignupResponse s)
{
	json j;
	j["status"] = s.status;
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(KeepAliveRequest k)
{
	json j;
	j["code"] = k.code;
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GeneralResponse generalResponse)
{
	json j;
	j["code"] = generalResponse.code;
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

//std::vector<char> JsonResponsePacketSerializer::serializeResponse(LogoutResponse loginResponse)
//{
//	
//}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse getRoomsResponse)
{
	json j;
	j["status"] = getRoomsResponse.status;
	j["rooms"] = (getRoomsResponse.rooms);
	j["id"] = getRoomsResponse.rooms.id;
	j["name"] = getRoomsResponse.rooms.name;
	j["maxPlayers"] = getRoomsResponse.rooms.maxPlayers;
	j["questionCount"] = getRoomsResponse.rooms.questionCount;
	j["timePerQuestion"] = getRoomsResponse.rooms.timePerQuestion;
	j["isActive"] = getRoomsResponse.rooms.isActive;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse getPlayersInRoomResponse)
{
	json j;
	j["rooms"] = getPlayersInRoomResponse.rooms;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse joinRoomResponse)
{
	json j;
	j["status"] = joinRoomResponse.status;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse createRoomResponse)
{
	json j;
	j["status"] = createRoomResponse.status;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(HighscoreResponse highscoreResponse)
{
	json j;
	j["status"] = highscoreResponse.status;
	//j["highscores"] = highscoreResponse.highscores;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}
