#pragma once
#include <WinSock2.h>
enum Protocol : byte
{
	GENERAL_RESPONSE = 10,
	RESPONSE_SIGNIN = 11,
	RESPONSE_SIGNOUT = 13,
	RESPONSE_SIGNUP = 14,
	RESPONSE_ERROR = 15,
	RESPOSNSE_CREATE_ROOM = 16,
	RESPONSE_JOIN_ROOM = 17,
	RESPONSE_GET_HIGHSCORE = 18,
	RESPONSE_GET_MY_STATS = 19,
	REQUEST_SIGNIN = 21,
	REQUEST_SIGNOUT = 23,
	REQUEST_SIGNUP = 24,
	REQUEST_CREATE_ROOM = 26,
	REQUEST_JOIN_ROOM = 27,
	REQUEST_GET_HIGHSCORE = 28,
	REQUEST_GET_MY_STATS = 29,
	REQUEST_KEEP_ALIVE = 32,
	RESPONSE_GET_ROOMS = 33,
	REQUEST_GET_ROOMS = 34,
	REQUEST_CLOSE_ROOM = 35,
	REQUEST_START_ROOM = 36,
	REQUEST_GET_ROOM_STATE = 37,
	REQUEST_LEAVE_ROOM = 38,
	RESPONSE_KEEP_ALIVE = 42,
	RESPONSE_CLOSE_ROOM = 44,
	RESPONSE_START_ROOM = 45,
	RESPONSE_LEAVE_ROOM = 46,
	RESPONSE_GET_ROOM_STATE = 46,
	REQUEST_GET_GAME_RESULTS = 51,
	REQUEST_SUBMIT_ANSWER = 52,
	REQUEST_GET_QUESTION = 53,
	REQUEST_LEAVE_GAME = 54,
	RESPONSE_GET_GAME_RESULTS = 61,
	RESPONSE_SUBMIT_ANSWER = 62,
	RESPONSE_GET_QUESTION = 63,
	RESPONSE_LEAVE_GAME = 64
};
// 29, 19 - May be removed