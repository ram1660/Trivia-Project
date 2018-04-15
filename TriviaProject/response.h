#include <iostream>
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
