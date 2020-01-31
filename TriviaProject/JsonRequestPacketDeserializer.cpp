#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer b)
{
	std::string bufferInString{(b.buffer).begin(), (b.buffer).end()};
	json j = json::parse(bufferInString);
	string userName = j["username"];
	string password = j["password"];
	LoginRequest login;

	login.username = userName;
	login.password = password;

	return login;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer b)
{
	std::string bufferInString{ (b.buffer).begin(), (b.buffer).end() };
	json j = json::parse(bufferInString);
	string userName = j["username"];
	string password = j["password"];
	string email = j["email"];

	SignupRequest signup;

	signup.username = userName;
	signup.password = password;
	signup.email = email;

	return signup;
}

SignoutRequest JsonRequestPacketDeserializer::deserializeSignoutRequest(Buffer b)
{
	std::string bufferInString{ (b.buffer).begin(), (b.buffer).end() };
	json j = json::parse(bufferInString);
	string username = j["username"];
	SignoutRequest signout;
	signout.username = username;
	return signout;
}

GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersRequest(Buffer b)
{
	std::string bufferInString{ (b.buffer).begin(), (b.buffer).end() };
	json j = json::parse(bufferInString);
	GetPlayersInRoomRequest request;
	string roomId = j["roomId"];
	request.roomId = atoi(roomId.c_str());
	return request;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(Buffer b)
{
	std::string bufferInString{ (b.buffer).begin(), (b.buffer).end() };
	json j = json::parse(bufferInString);
	JoinRoomRequest request;
	string username = j["username"];
	string roomId = j["roomId"];
	request.username = username;
	request.roomId = atoi(roomId.c_str());
	return request;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(Buffer b)
{
	std::string bufferInString{ (b.buffer).begin(), (b.buffer).end() };
	json j = json::parse(bufferInString);
	CreateRoomRequest request;
	string username = j["username"];
	string roomName = j["roomName"];
	string maxUsers = j["maxUsers"];
	string questionCount = j["questionCount"];
	string answerTimeout = j["answerTimeout"];
	request.roomName = roomName;
	request.maxUsers = atoi(maxUsers.c_str());
	request.questionCount = atoi(questionCount.c_str());
	request.answerTimeout = atoi(answerTimeout.c_str());
	request.username = username;
	return request;
}

SubmitAnswerRequest JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(Buffer b)
{
	std::string bufferInString{ (b.buffer).begin(), (b.buffer).end() };
	json j = json::parse(bufferInString);
	SubmitAnswerRequest request;
	std::string answerId = j["answerId"];
	request.answerId = std::atoi(answerId.c_str());
	return request;
}
