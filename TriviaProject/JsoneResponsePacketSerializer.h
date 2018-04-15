#pragma once
#include "response.h"
class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorRepose s);
	static Buffer serializeResponse(LoginResponse s);
	static Buffer serializeResponse(SignupResponse s);
	

};

