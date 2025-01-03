#pragma once

#include "../../Game/Game.h"

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/Button/Button.h"

#include "../../Server/Server.h"
#include "../../Client/Client.h"

#include <enet/enet.h>

#include <memory>

class InGameVisualInterface : virtual public VisualInterface
{
private:
	InGameVisualInterface();
	virtual ~InGameVisualInterface();
	InGameVisualInterface(const InGameVisualInterface& other) = delete;
	InGameVisualInterface& operator= (const InGameVisualInterface& other) = delete;
	InGameVisualInterface(const InGameVisualInterface&& other) = delete;
	InGameVisualInterface& operator= (const InGameVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	Button backButton;

	Game::Status gameStatusItCameFrom;


	std::shared_ptr<Server> server;
	std::shared_ptr<Client> client;

	int receivedNumDicesPerUser;
	std::string receivedServerIP;
	enet_uint16 receivedServerPort;
	std::string receivedUsername;

public:
	static InGameVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;

	inline void setReceivedNumDicesPerUser(int receivedNumDicesPerUser) { this->receivedNumDicesPerUser = receivedNumDicesPerUser; }
	inline void setReceivedServerIP(const std::string& receivedServerIP) { this->receivedServerIP = receivedServerIP; }
	inline void setReceivedServerPort(enet_uint16 receivedServerPort) { this->receivedServerPort = receivedServerPort; }
	inline void setReceivedUsername(const std::string& receivedUsername) { this->receivedUsername = receivedUsername; }
};