#pragma once
#include <iostream>
#include "structures.h"
#include "json.hpp"
using json = nlohmann::json;
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer b);
	static SignupRequest deserializeSignupRequest(Buffer b);
	static SignoutRequest deserializeSignoutRequest(Buffer b);
	static GetPlayersInRoomRequest deserializeGetPlayersRequest(Buffer b);
	static JoinRoomRequest deserializeJoinRoomRequest(Buffer b);
	static CreateRoomRequest deserializeCreateRoomRequest(Buffer b);
};
