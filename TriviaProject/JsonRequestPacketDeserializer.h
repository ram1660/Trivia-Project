#pragma once
#include <iostream>
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer b);
	static SignupRequest deserializeLoginRequest(Buffer b);
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};