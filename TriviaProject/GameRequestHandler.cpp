#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler()
{
}

GameRequestHandler::GameRequestHandler(LoggedUser user, Game* game, GameManager* gameManager, RequestHandlerFactory* factory) : m_user(user), m_game(game), m_gameManager(gameManager), m_handlerFactory(factory)
{
}

bool GameRequestHandler::isRequestRelevant(Request r)
{
	if (r.id == REQUEST_GET_QUESTION || r.id == REQUEST_SUBMIT_ANSWER || r.id == REQUEST_GET_GAME_RESULTS || r.id == REQUEST_LEAVE_GAME)
		return true;
	return false;
}

RequestResult GameRequestHandler::handleRequest(Request r)
{
	if (r.id == REQUEST_GET_QUESTION)
		return getQuestion(r);
	else if (r.id == REQUEST_SUBMIT_ANSWER)
		return submitAnswer(r);
	else if (r.id == REQUEST_GET_GAME_RESULTS)
		return getGameResults(r);
	else
		return leaveGame(r);
}

RequestResult GameRequestHandler::getQuestion(Request r)
{
	RequestResult result;
	Buffer buffer;
	GetQuestionResponse response;
	Question userQuestion = m_game->getQuestionForUser(m_user);
	response.question = userQuestion.getQuestion();
	for (size_t i = 0; i < userQuestion.getPossibleAnswers().size(); i++)
	{
		response.answers.insert(std::make_pair(i, userQuestion.getPossibleAnswers()[i]));
	}
	response.status = RESPONSE_GET_QUESTION;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}

RequestResult GameRequestHandler::submitAnswer(Request r)
{
	RequestResult result;
	Buffer buffer;
	SubmitAnswerResponse response;
	buffer.buffer = r.buffer;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(buffer);
	unsigned int userAnswer = request.answerId;
	m_game->submitAnswer(userAnswer);

	return RequestResult();
}

RequestResult GameRequestHandler::getGameResults(Request r)
{
	RequestResult result;
	Buffer buffer;
	return RequestResult();
}

RequestResult GameRequestHandler::leaveGame(Request r)
{
	RequestResult result;
	Buffer buffer;
	return RequestResult();
}
