#include "JsonRequestPacketDeserializer.h"

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(Buffer b)
{
	LoginRequest request;
	request.username = b.buffer[2];
	return request;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignupRequest(Buffer b)
{
	SignupRequest request;

	request.username = 
}
