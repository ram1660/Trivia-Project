#include "JsonRequestPacketDeserializer.h"
#include "structures.h"
#include "json.hpp"

using json = nlohmann::json;

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