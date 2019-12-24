#pragma once
#include <iostream>
#include "structures.h"
#include <string>
#include "json.hpp"
class JsonResponsePacketSerializer
{
public:
	static std::vector<char> serializeResponse(ErrorResponse);
	static std::vector<char> serializeResponse(LoginResponse);
	static std::vector<char> serializeResponse(SignupResponse);
	static std::vector<char> serializeResponse(KeepAliveRequest);
	static std::vector<char> serializeResponse(GeneralResponse);
};
