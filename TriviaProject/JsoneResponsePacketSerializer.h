#pragma once
#include <iostream>
#include "structures.h"
#include "Buffer.h"
#include "json.hpp"
using json = nlohmann::json;
class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse s);
	static Buffer serializeResponse(LoginResponse s);
	static Buffer serializeResponse(SignupResponse s);
	
};

