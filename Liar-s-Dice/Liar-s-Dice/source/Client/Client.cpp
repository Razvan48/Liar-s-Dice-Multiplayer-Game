#include "Client.h"

#include "../GlobalClock/GlobalClock.h"

#include <json.hpp>

#include <iostream>

Client::Client(const std::string& serverIP, enet_uint16 serverPort, const std::string& username)
	: MAX_NUM_SERVERS(1), NUM_CHANNELS(1), TIME_WAITING_FOR_EVENTS_MS(0)
	, serverPeer(nullptr), client(nullptr), serverAddress()
	, lastTimeTriedConnection(0.0f)
	, RETRY_CONNECTION_DELTA_TIME(1.0f)
	, isConnected(false)
	, TIME_BETWEEN_PINGS(1.0f)
	, lastTimeSentPing(0.0f)
	, username(username)
	, lastTimeTriedToSendInitialName(0.0f)
	, hasToSendInitialName(true)
	, TIME_BETWEEN_INITIAL_NAME_SENDINGS(1.0f)
{
	this->client = enet_host_create(NULL, this->MAX_NUM_SERVERS, this->NUM_CHANNELS, 0, 0); // 0, 0 inseamna fara limite la latimea de banda
	if (client == NULL)
	{
		std::cout << "Error: ENet failed to create client" << std::endl;
	}

	enet_address_set_host(&this->serverAddress, serverIP.c_str());
	this->serverAddress.port = serverPort;

	std::cout << "Client " << this->username << " initialized with : " << this->serverAddress.host << ' ' << this->serverAddress.port << std::endl;
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
	std::cout << "In handlePacket in Client named " << this->username << std::endl;

	if (eNetEvent.packet->dataLength == 0)
	{
		std::cout << "Warning: Client received empty packet" << std::endl;
		return;
	}


	// Rezolvare Pachet

	std::string receivedMessage((char*)eNetEvent.packet->data);
	std::cout << "Client received Message: " << receivedMessage << " from server, size = " << receivedMessage.size() << std::endl;

	nlohmann::json receivedMessageJSON = nlohmann::json::parse(receivedMessage);

	// Fara Ping-uri !!!


	if (receivedMessageJSON.contains("name"))
		this->username = receivedMessageJSON["name"];

	enet_packet_destroy(eNetEvent.packet);
}

void Client::update()
{
	if (!this->isConnected)
	{
		if (GlobalClock::get().getCurrentTime() - this->lastTimeTriedConnection > this->RETRY_CONNECTION_DELTA_TIME)
		{
			this->lastTimeTriedConnection = GlobalClock::get().getCurrentTime();
			this->serverPeer = enet_host_connect(this->client, &this->serverAddress, this->NUM_CHANNELS, 0); // 0 = nu trimitem nimic
			if (this->serverPeer == NULL)
				std::cout << "Warning: No available peers for initiating an ENet connection (no server available). Retrying..." << std::endl;
			else
			{
				std::cout << "Client " << this->username << " connected to server" << std::endl;
				this->isConnected = true;
			}
		}

		return;
	}

	// Trimitem ce informatii vitale stim deja catre server.
	if (this->hasToSendInitialName)
	{
		if (GlobalClock::get().getCurrentTime() - this->lastTimeTriedToSendInitialName > this->TIME_BETWEEN_INITIAL_NAME_SENDINGS)
		{
			this->lastTimeTriedToSendInitialName = GlobalClock::get().getCurrentTime();

			nlohmann::json messageToSendJSON;
			messageToSendJSON["initialName"] = this->username;
			this->sendMessage(messageToSendJSON.dump(), this->hasToSendInitialName, this->lastTimeSentPing);
		}
	}

	// Vedem ce pachete am primit.
	// code = 0 inseamna ca nu a fost niciun eveniment
	ENetEvent eNetEvent;
	int code = enet_host_service(this->client, &eNetEvent, this->TIME_WAITING_FOR_EVENTS_MS);
	while (code > 0)
	{
		switch (eNetEvent.type)
		{
		case ENET_EVENT_TYPE_RECEIVE:
			this->handlePacket(eNetEvent);
			break;
		default:
			std::cout << "Warning: Client " << this->username << " received unrecognized event type" << std::endl;
			break;
		}

		code = enet_host_service(this->client, &eNetEvent, this->TIME_WAITING_FOR_EVENTS_MS);
	}
	if (code < 0)
	{
		std::cout << "Error: Client service for client " << this->username << " failed" << std::endl;
	}

	// Apoi trimitem ping-ul catre server.
	if (GlobalClock::get().getCurrentTime() - this->lastTimeSentPing > this->TIME_BETWEEN_PINGS)
	{
		nlohmann::json messageToSendJSON;
		messageToSendJSON["ping"] = true;
		messageToSendJSON["name"] = this->username;

		this->sendMessageUnsafe(messageToSendJSON.dump(), this->lastTimeSentPing);
	}
}



