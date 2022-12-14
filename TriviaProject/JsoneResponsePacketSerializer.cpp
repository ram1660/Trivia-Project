#include "JsoneResponsePacketSerializer.h"

namespace ns
{
	typedef struct RoomData
	{
		unsigned int id;
		std::string name;
		unsigned int maxPlayers;
		unsigned int questionCount;
		unsigned int timePerQuestion;
		unsigned int isActive;
	} RoomData;

	typedef struct PlayerResults
	{
		std::string username;
		unsigned int correctAnswerCount;
		unsigned int wrongAnswerCount;
		unsigned int averageAnswerTime;
	}PlayerResults;

	void to_json(nlohmann::json& j, const ns::RoomData& val)
	{
		j["id"] = val.id;
		j["name"] = val.name;
		j["maxPlayers"] = val.maxPlayers;
		j["questionCount"] = val.questionCount;
		j["timePerQuestion"] = val.timePerQuestion;
		j["isActive"] = val.isActive;
	}
	void to_json(nlohmann::json& j, const ns::PlayerResults& val)
	{
		j["username"] = val.username;
		j["correctAnswerCount"] = val.correctAnswerCount;
		j["wrongAnswerCount"] = val.wrongAnswerCount;
		j["averageAnswerTime"] = val.averageAnswerTime;
	}
}

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
	vector<ns::RoomData> newRooms;
	for (RoomData* room : getRoomsResponse.rooms)
	{
		newRooms.push_back(ns::RoomData{ room->id, room->name, room->maxPlayers, room->questionCount, room->timePerQuestion, room->isActive });
		delete room;
	}
	j["status"] = getRoomsResponse.status;
	j["rooms"] = newRooms;
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
	j["highscores"] = highscoreResponse.highscores;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse closeRoomResponse)
{
	json j;
	j["status"] = closeRoomResponse.status;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(StartRoomResponse startRoomResponse)
{
	json j;
	j["status"] = startRoomResponse.status;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse getRoomStateResponse)
{
	json j;
	j["status"] = getRoomStateResponse.status;
	j["hasGameBegun"] = getRoomStateResponse.hasGameBegun;
	j["players"] = getRoomStateResponse.players;
	j["questionCount"] = getRoomStateResponse.questionCount;
	j["answerTimeout"] = getRoomStateResponse.answerTimeout;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse leaveRoomResponse)
{
	json j;
	j["status"] = leaveRoomResponse.status;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse getQuestionResponse)
{
	json j;
	j["status"] = getQuestionResponse.status;
	j["question"] = getQuestionResponse.question;
	j["answers"] = getQuestionResponse.answers; // Fix?
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse submitAnswerResponse)
{
	json j;
	j["status"] = submitAnswerResponse.status;
	j["correctAnswer"] = submitAnswerResponse.correctAnswer;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse getGameResultsResponse)
{
	json j;
	vector<ns::PlayerResults> newResults;
	j["status"] = getGameResultsResponse.status;
	for (PlayerResults result : getGameResultsResponse.results)
		newResults.push_back(ns::PlayerResults{ result.username, result.correctAnswerCount, result.wrongAnswerCount, result.averageAnswerTime });
	j["playersResults"] = newResults;
	string str = j.dump();
	vector<char> buffer(str.begin(), str.end());
	return buffer;
}
