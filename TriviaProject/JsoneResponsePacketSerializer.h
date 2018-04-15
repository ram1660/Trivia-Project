#pragma once
class JsonResponsePacketSerializer
{
public:
	static Buffer serializeResponse(ErrorRepose s);
	static Buffer serializeResponse(LoginRepsone s);
	static Buffer serializeResponse(SignupReponse s);

};

