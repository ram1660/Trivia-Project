#pragma once
#include <iostream>
#include "structures.h"+
class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorResponse s);
	static Buffer serializeResponse(LoginResponse s);
	static Buffer serializeResponse(SignupResponse s);
	

};


