#include "Server.h"

#include "../RandomGenerator/RandomGenerator.h"
#include "../GlobalClock/GlobalClock.h"

#include <iostream>
#include <json.hpp>

#include <set>

Server::Server(int numDicesPerUser)
	: MAX_NUM_CLIENTS(64), NUM_CHANNELS(2), TIME_WAITING_FOR_EVENTS_MS(0)
	, server(nullptr), address(), MINIMUM_PORT(10000), MAXIMUM_PORT(20000)
	, succesfullyCreated(false), lastTimeTriedCreation(0.0f), RETRY_CREATION_DELTA_TIME(1.0f)
	, MAXIMUM_TIME_BEFORE_DECLARING_CONNECTION_LOST(5.0f)
	, NUM_DICES_PER_USER(numDicesPerUser)
{
	this->address.host = ENET_HOST_ANY;
	this->address.port = RandomGenerator::randomUniformInt(this->MINIMUM_PORT, this->MAXIMUM_PORT);
}

Server::~Server()
{
	for (int i = 0; i < this->users.size(); ++i)
	{
		if (this->users[i].peer != nullptr)
			enet_peer_disconnect(this->users[i].peer, 0);
	}

	if (this->server != nullptr)
		enet_host_destroy(this->server);
}

void Server::sendMessage(const User& user, const std::string& messageToSend, bool& failedToSendMessage) const
{
	ENetPacket* packet = enet_packet_create(messageToSend.c_str(), messageToSend.size() + 1, ENET_PACKET_FLAG_RELIABLE);

	// 0 daca a avut succes
	if (enet_peer_send(user.peer, 0, packet) == 0)
		failedToSendMessage = false;
	else
	{
		failedToSendMessage = true;
		std::cout << "Error: Server failed to send message to " << user.username << std::endl;
	}
}

void Server::sendMessageUnsafe(const User& user, const std::string& messageToSend) const
{
	ENetPacket* packet = enet_packet_create(messageToSend.c_str(), messageToSend.size() + 1, ENET_PACKET_FLAG_RELIABLE);

	// 0 daca a avut succes
	if (enet_peer_send(user.peer, 0, packet) != 0)
		std::cout << "Error: Server failed to send message to " << user.username << std::endl;
}

std::string Server::allocateNewName(const std::string& initialName)
{
	if (this->usernameFrequency.find(initialName) == this->usernameFrequency.end())
		this->usernameFrequency[initialName] = 1;
	else
		++this->usernameFrequency[initialName];

	return initialName + "-" + std::to_string(this->usernameFrequency[initialName]);
}

void Server::handlePacket(const ENetEvent& eNetEvent)
{
	std::cout << "In handlePacket in Server" << std::endl;

	if (eNetEvent.packet->dataLength == 0)
	{
		std::cout << "Warning: Server received empty packet" << std::endl;
		return;
	}




	// Rezolvare Pachet

	std::string receivedMessage((char*)eNetEvent.packet->data);
	std::cout << "Server received message: " << receivedMessage << ", size = " << receivedMessage.size() << std::endl;

	nlohmann::json receivedMessageJSON = nlohmann::json::parse(receivedMessage);

	if (receivedMessageJSON.contains("name"))
	{
		for (int i = 0; i < this->users.size(); ++i)
		{
			if (this->users[i].username == receivedMessageJSON["name"])
			{
				this->users[i].lastTimeSentPingToServer = GlobalClock::get().getCurrentTime();
			}
		}
	}


	if (receivedMessageJSON.contains("initialName"))
	{
		if (this->users.size() == this->MAX_NUM_CLIENTS)
		{
			std::cout << "Warning: Server reached maximum number of clients and could not allow a recently arrived client to connect" << std::endl;
		}
		else
		{
			User newUser;
			newUser.peer = eNetEvent.peer;
			newUser.username = this->allocateNewName(receivedMessageJSON["initialName"]);
			newUser.lastTimeSentPingToServer = GlobalClock::get().getCurrentTime();
			this->users.push_back(newUser);
		}

		return;
	}


	enet_packet_destroy(eNetEvent.packet);
}

void Server::update()
{
	if (!this->succesfullyCreated)
	{
		if (GlobalClock::get().getCurrentTime() - this->lastTimeTriedCreation > this->RETRY_CREATION_DELTA_TIME)
		{
			this->lastTimeTriedCreation = GlobalClock::get().getCurrentTime();
			this->server = enet_host_create(&this->address, this->MAX_NUM_CLIENTS, this->NUM_CHANNELS, 0, 0); // 0, 0 inseamna fara limite pe latimea de banda

			if (this->server == nullptr)
			{
				std::cout << "Error: ENet server host creation failed, trying again..." << std::endl;
			}
			else
			{
				this->succesfullyCreated = true;
				std::cout << "Server started on port " << this->address.port << std::endl;
			}
		}

		return;
	}


	// Vedem ce pachete am primit.
	// code = 0 inseamna ca nu a fost niciun eveniment
	ENetEvent eNetEvent;
	int code = enet_host_service(this->server, &eNetEvent, this->TIME_WAITING_FOR_EVENTS_MS);
	while (code > 0)
	{
		switch (eNetEvent.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			std::cout << "Client connected" << std::endl;
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			this->handlePacket(eNetEvent);
			break;
		default:
			std::cout << "Warning: Server received unrecognized event type" << std::endl;
			break;
		}

		code = enet_host_service(this->server, &eNetEvent, this->TIME_WAITING_FOR_EVENTS_MS);
	}
	if (code < 0)
	{
		std::cout << "Error: Server service failed" << std::endl;
	}


	// Mai vedem daca ne ramasese ceva de trimis la vreun client ce a esuat.
	for (int i = 0; i < this->users.size(); ++i)
	{
		if (this->users[i].hasToSendName)
		{
			nlohmann::json messageToSendJSON;
			messageToSendJSON["name"] = this->users[i].username;
			this->sendMessage(this->users[i], messageToSendJSON.dump(), this->users[i].hasToSendName);
		}
	}


	// Eliminam din structura de date user-ii pierduti.
	for (int i = 0; i < this->users.size(); ++i)
	{
		if (GlobalClock::get().getCurrentTime() - this->users[i].lastTimeSentPingToServer > this->MAXIMUM_TIME_BEFORE_DECLARING_CONNECTION_LOST)
		{
			std::cout << "Client " << this->users[i].username << " lost connection to server" << std::endl;
			enet_peer_disconnect(this->users[i].peer, 0);

			for (int j = i + 1; j < this->users.size(); ++j)
				this->users[j - 1] = this->users[j];
			this->users.pop_back();

			--i;
		}
	}
}





