#include "GameRequestHandler.h"

GameRequestHandler::GameRequestHandler()
{
}

GameRequestHandler::GameRequestHandler(LoggedUser* user, Game* game, GameManager* gameManager, RequestHandlerFactory* factory) : m_user(user), m_game(game), m_gameManager(gameManager), m_handlerFactory(factory)
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
	for (unsigned int i = 0; i < userQuestion.getPossibleAnswers().size(); i++)
		response.answers.insert(std::make_pair(i, userQuestion.getPossibleAnswers()[i]));
	response.status = RESPONSE_GET_QUESTION;
	buffer.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	result.response = buffer;
	return result;
}
// Extract from the client the time for submitted answer. - Done
RequestResult GameRequestHandler::submitAnswer(Request r)
{
	RequestResult result;
	Buffer buffer;
	SubmitAnswerResponse response;
	buffer.buffer = r.buffer;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(buffer);
	unsigned int userAnswer = request.answerId;
	response.status = RESPONSE_SUBMIT_ANSWER;
	response.correctAnswer = m_game->submitAnswer(userAnswer, *m_user);
	result.response.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult GameRequestHandler::getGameResults(Request r)
{
	RequestResult result;
	Buffer buffer;
	GetGameResultsResponse response;
	response.status = RESPONSE_GET_GAME_RESULTS;
	response.results = m_gameManager->getPlayersResults();
	result.response.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}

RequestResult GameRequestHandler::leaveGame(Request r)
{
	RequestResult result;
	GeneralResponse response;
	response.code = GENERAL_RESPONSE;
	m_game->removePlayer(m_user->getUsername());
	result.response.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return result;
}
