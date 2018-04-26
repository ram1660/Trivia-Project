#pragma once
#include <iostream>
#include "Structs.h"
#include "json.hpp"
using json = nlohmann::json;
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer b);
	static SignupRequest deserializeSignupRequest(Buffer b);
};