#include "JsonRequestPacketDeserializer.h"
using namespace std;
using nlohmann::json;


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer b)
{
	
	LoginRequest lr;
	json j = b.buffer;
	lr.username = j["username"].get<std::string>();
	lr.password = j["password"].get<std::string>();

	return lr;
	
	//return null;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer b)
{
		SignupRequest sr;
	json j = b.buffer;
	sr.email = j["email"].get<std::string>();
	sr.password = j["password"].get<std::string>();
	sr.username = j["username"].get<std::string>();
	return sr;
	
	//return Null;
}
