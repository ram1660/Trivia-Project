#pragma once
class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(Buffer b);
	static SignupRequest deserializeLoginRequest(Buffer b);
};

