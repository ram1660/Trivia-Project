#pragma once
#include <iostream>
#include "structures.h"
#include "json.hpp"
//#include "Buffer.h"
using json = nlohmann::json;
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer b);
	static SignupRequest deserializeSignupRequest(Buffer b);
};