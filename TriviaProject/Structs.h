#pragma once
#include <iostream>
#include "IRequestHandler.h"
#include "Buffer.h"
struct LoginResponse
{
	unsigned int status;
};

struct SignupResponse
{
	unsigned int status;
};

struct ErrorResponse
{
	std::string message;
};

struct LoginRequest
{
	std::string username;
	std::string password;
};

struct SignupRequest
{
	std::string username;
	std::string password;
	std::string email;
};

struct RequestResult
{
	Buffer response;
	IRequestHandler newHandler;
};
struct Request
{
	RequestId id;
	receivalTime ctime;
	Buffer buffer;
};