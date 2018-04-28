#include "JsoneResponsePacketSerializer.h"

Buffer JsonResponsePacketSerializer::serializeResponse(ErrorResponse s)
{
	Buffer buffer;
	json j = s.message;
	buffer.buffer = json::to_msgpack(s);
	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(LoginResponse s)
{
	Buffer buffer;
	json j = s.status;
	buffer.buffer = json::to_msgpack(s);
	return buffer;
}

Buffer JsonResponsePacketSerializer::serializeResponse(SignupResponse s)
{
	Buffer buffer;
	json j = s.status;
	buffer.buffer = json::to_msgpack(s);
	return buffer;
}
