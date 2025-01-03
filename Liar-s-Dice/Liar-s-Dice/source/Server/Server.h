#pragma once

#include <enet/enet.h>

#include <string>
#include <vector>
#include <map>

class Server
{
public:
	struct User
	{
		ENetPeer* peer;
		std::string username;
		float lastTimeSentPingToServer;

		bool hasToSendName;

		User()
			: peer(nullptr)
			, username("")
			, lastTimeSentPingToServer(0.0f)

			, hasToSendName(true)
		{

		}
	};

private:
	const int MAX_NUM_CLIENTS;
	const int NUM_CHANNELS;
	const int TIME_WAITING_FOR_EVENTS_MS;
	ENetHost* server;
	ENetAddress address;

	const int MINIMUM_PORT;
	const int MAXIMUM_PORT;

	bool succesfullyCreated;
	float lastTimeTriedCreation;
	const float RETRY_CREATION_DELTA_TIME;

	const float MAXIMUM_TIME_BEFORE_DECLARING_CONNECTION_LOST;

	std::map<std::string, int> usernameFrequency;
	std::vector<User> users;

	const int NUM_DICES_PER_USER;

	std::string allocateNewName(const std::string& initialName);
	void handlePacket(const ENetEvent& eNetEvent);

public:
	Server(int numDicesPerUser);
	~Server();

	void sendMessage(const User& user, const std::string& messageToSend, bool& failedToSendMessage) const;
	void sendMessageUnsafe(const User& user, const std::string& messageToSend) const;

	void update();

	enet_uint16 getPort() const { return this->address.port; }
};

