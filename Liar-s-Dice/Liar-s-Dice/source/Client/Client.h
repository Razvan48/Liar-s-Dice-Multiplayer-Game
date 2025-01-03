#pragma once

#include <string>
#include <enet/enet.h>

class Client
{
private:
	const int MAX_NUM_SERVERS; // Numarul maxim de server-e la care poate fi clientul conectat
	const int NUM_CHANNELS;
	const int TIME_WAITING_FOR_EVENTS_MS;

	ENetPeer* serverPeer;
	ENetHost* client;
	ENetAddress serverAddress;

	const float RETRY_CONNECTION_DELTA_TIME;

	const float TIME_BETWEEN_PINGS;
	float lastTimeSentPing;

	std::string clientName;

	bool hasToSendName;

	void handlePacket(const ENetEvent& eNetEvent);

public:
	Client(const std::string& serverIP, enet_uint16 serverPort, const std::string& clientName);
	~Client();

	void update();

	void sendMessage(const std::string& messageToSend, bool& failedToSendMessage, float& timeWhenMessageSent) const;
	void sendMessageUnsafe(const std::string& messageToSend, float& timeWhenMessageSent) const;
	void sendMessageUnsafe(const std::string& messageToSend) const;
};

