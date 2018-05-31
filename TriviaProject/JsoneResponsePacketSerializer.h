#pragma once
#include <iostream>
#include "structures.h"
#include <string>
#include "json.hpp"
class JasonResponsePacketSerializer
{
public:
	std::vector<char> serializeResponse(ErrorResponse);
	std::vector<char> serializeResponse(LoginResponse);
	std::vector<char> serializeResponse(SignupResponse);
};
