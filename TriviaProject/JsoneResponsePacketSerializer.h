#pragma once
#include <iostream>
class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse s);
	static Buffer serializeResponse(LoginResponse s);
	static Buffer serializeResponse(SignupResponse s);
	

};

struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};

