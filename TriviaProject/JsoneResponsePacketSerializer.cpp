#include "JsoneResponsePacketSerializer.h"
using nlohmann::json;
std::vector<char> JasonResponsePacketSerializer::serializeResponse(ErrorResponse e)
{
	json j;
	j["message"] = e.message;		
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JasonResponsePacketSerializer::serializeResponse(LoginResponse l)
{
	json j;
	j["status"] = l.status;
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}

std::vector<char> JasonResponsePacketSerializer::serializeResponse(SignupResponse s)
{
	json j;
	j["status"] = s.status;
	std::string str = j.dump();
	std::vector<char> buffer(str.begin(), str.end());
	return buffer;
}
