#include "Client.h"

#include "../GlobalClock/GlobalClock.h"

#include <json.hpp>

#include <iostream>

Client::Client(const std::string& serverIP, enet_uint16 serverPort, const std::string& clientName)
	: MAX_NUM_SERVERS(1), NUM_CHANNELS(1), TIME_WAITING_FOR_EVENTS_MS(0)
	, serverPeer(nullptr), client(nullptr), serverAddress()
	, RETRY_CONNECTION_DELTA_TIME(1.0f)
	, TIME_BETWEEN_PINGS(1.0f)
	, lastTimeSentPing(0.0f)
	, clientName(clientName)
	, hasToSendName(true)
{
	this->client = enet_host_create(NULL, this->MAX_NUM_SERVERS, this->NUM_CHANNELS, 0, 0); // 0, 0 inseamna fara limite la latimea de banda
	if (client == NULL)
	{
		std::cout << "Error: ENet failed to create client" << std::endl;
	}

	enet_address_set_host(&this->serverAddress, serverIP.c_str());
	this->serverAddress.port = serverPort;

	std::cout << "Client " << this->clientName << " initialized with : " << this->serverAddress.host << ' ' << this->serverAddress.port << std::endl;

	bool connectedToServer = false;
	float lastTimeTriedConnectingToServer = 0.0f;
	while (!connectedToServer)
	{
		if (GlobalClock::get().getCurrentTime() - lastTimeTriedConnectingToServer > this->RETRY_CONNECTION_DELTA_TIME)
		{
			lastTimeTriedConnectingToServer = GlobalClock::get().getCurrentTime();
			this->serverPeer = enet_host_connect(this->client, &this->serverAddress, this->NUM_CHANNELS, 0); // 0 = nu trimitem nimic
			if (this->serverPeer == NULL)
				std::cout << "Warning: No available peers for initiating an ENet connection (no server available). Retrying..." << std::endl;
			else
			{
				std::cout << "Client " << this->clientName << " connected to server" << std::endl;
				connectedToServer = true;
			}
		}
	}
}

Client::~Client()
{
	if (this->client != nullptr)
		enet_host_flush(this->client);
	if (this->serverPeer != nullptr)
		enet_peer_disconnect(this->serverPeer, 0);
	if (this->client != nullptr)
		enet_host_destroy(this->client);
}

void Client::sendMessage(const std::string& messageToSend, bool& failedToSendMessage, float& timeWhenMessageSent) const
{
	ENetPacket* packet = enet_packet_create(messageToSend.c_str(), messageToSend.size() + 1, ENET_PACKET_FLAG_RELIABLE);

	// 0 daca a avut succes
	if (enet_peer_send(this->serverPeer, 0, packet) == 0)
	{
		failedToSendMessage = false;
		timeWhenMessageSent = GlobalClock::get().getCurrentTime();

		std::cout << "Client sent message: " << messageToSend << std::endl;
	}
	else
	{
		failedToSendMessage = true;
		std::cout << "Error: Client failed to send message" << std::endl;
	}
}

void Client::sendMessageUnsafe(const std::string& messageToSend, float& timeWhenMessageSent) const
{
	ENetPacket* packet = enet_packet_create(messageToSend.c_str(), messageToSend.size() + 1, ENET_PACKET_FLAG_RELIABLE);

	// 0 daca a avut succes
	if (enet_peer_send(this->serverPeer, 0, packet) == 0)
	{
		timeWhenMessageSent = GlobalClock::get().getCurrentTime();

		std::cout << "Client sent message: " << messageToSend << std::endl;
	}
	else
		std::cout << "Error: Client failed to send message" << std::endl;
}

void Client::sendMessageUnsafe(const std::string& messageToSend) const
{
	ENetPacket* packet = enet_packet_create(messageToSend.c_str(), messageToSend.size() + 1, ENET_PACKET_FLAG_RELIABLE);

	// 0 daca a avut succes
	if (enet_peer_send(this->serverPeer, 0, packet) == 0)
		std::cout << "Client sent message: " << messageToSend << std::endl;
	else
		std::cout << "Error: Client failed to send message" << std::endl;
}

void Client::handlePacket(const ENetEvent& eNetEvent)
{
	std::cout << "In handlePacket in Client named " << this->clientName << std::endl;

	if (eNetEvent.packet->dataLength == 0)
	{
		std::cout << "Warning: Client received empty packet" << std::endl;
		return;
	}


	// Handling Packet

	std::string receivedMessage((char*)eNetEvent.packet->data);
	std::cout << "Received Message: " << receivedMessage << " from server, size = " << receivedMessage.size() << std::endl;

	nlohmann::json receivedMessageJSON = nlohmann::json::parse(receivedMessage);

	// fara ping-uri

	enet_packet_destroy(eNetEvent.packet);
}

void Client::update()
{
	// Trimitem ce informatii vitale stim deja catre server.
	if (this->hasToSendName)
	{
		nlohmann::json messageToSendJSON;
		messageToSendJSON["name"] = this->clientName;
		this->sendMessage(messageToSendJSON.dump(), this->hasToSendName, this->lastTimeSentPing);
	}

	// Vedem ce pachete am primit.
	// code = 0 inseamna ca nu a fost niciun eveniment
	ENetEvent eNetEvent;
	int code = enet_host_service(this->client, &eNetEvent, this->TIME_WAITING_FOR_EVENTS_MS);
	if (code > 0)
	{
		switch (eNetEvent.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			this->handlePacket(eNetEvent);
			break;
		default:
			std::cout << "Warning: Client " << this->clientName << " received unrecognized event type" << std::endl;
			break;
		}
	}
	else if (code < 0)
	{
		std::cout << "Error: Client service for client " << this->clientName << " failed" << std::endl;
	}

	// Apoi trimitem ping-ul catre server.
	if (GlobalClock::get().getCurrentTime() - this->lastTimeSentPing > this->TIME_BETWEEN_PINGS)
	{
		nlohmann::json messageToSendJSON;
		messageToSendJSON["ping"] = true;

		this->sendMessageUnsafe(messageToSendJSON.dump(), this->lastTimeSentPing);
	}
}



