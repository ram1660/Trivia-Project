#include "JsonRequestPacketDeserializer.h"
#include "structures.h"
#include "json.hpp"

using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer b)
{
	json j = json::from_msgpack(b.buffer);
	string userName = j["username"];
	string password = j["password"];
	LoginRequest login;

	login.username = userName;
	login.password = password;

	return login;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer b)
{
	json j = json::from_msgpack(b.buffer);
	string userName = j["username"];
	string password = j["password"];
	string email = j["email"];

	SignupRequest signup;

	signup.username = userName;
	signup.password = password;
	signup.email = email;

	return signup;
}