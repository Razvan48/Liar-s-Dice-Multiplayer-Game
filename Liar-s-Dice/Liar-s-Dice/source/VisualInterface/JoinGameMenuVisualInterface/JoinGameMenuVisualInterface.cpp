#include "JoinGameMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

#include "../../AssetManager/AssetManager.h"

#include "../InGameVisualInterface/InGameVisualInterface.h"

JoinGameMenuVisualInterface::JoinGameMenuVisualInterface()
	: backgroundEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth()
		, WindowManager::get().getWindowHeight()
		, 0.0f, "inputMenuBackgroundTexture")
	, usernameTextEntity(WindowManager::get().getWindowWidth() / 5.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 2.5f
		, WindowManager::get().getWindowHeight() / 10.0f, 0.0f, "Username:")
	, usernameDataBox(WindowManager::get().getWindowWidth() / 1.5f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 1.75f
		, WindowManager::get().getWindowHeight() / 10.0f
		, 0.0f, "dataBoxTexture", "username")
	, fullAddressTextEntity(WindowManager::get().getWindowWidth() / 5.0f
		, WindowManager::get().getWindowHeight() / 3.0f
		, WindowManager::get().getWindowWidth() / 2.5f
		, WindowManager::get().getWindowHeight() / 10.0f, 0.0f, "Full Address:")
	, fullAddressDataBox(WindowManager::get().getWindowWidth() / 1.5f
		, WindowManager::get().getWindowHeight() / 3.0f
		, WindowManager::get().getWindowWidth() / 1.75f
		, WindowManager::get().getWindowHeight() / 10.0f
		, 0.0f, "dataBoxTexture", "fulladdress")
	, joinGameButton(9.0f * WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 5.5f
		, WindowManager::get().getWindowHeight() / 10.0f
		, 0.0f, "Join Game", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, backButton(WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 5.5f
		, WindowManager::get().getWindowHeight() / 10.0f
		, 0.0f, "Back", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
{

}

JoinGameMenuVisualInterface::~JoinGameMenuVisualInterface()
{

}

JoinGameMenuVisualInterface& JoinGameMenuVisualInterface::get()
{
	static JoinGameMenuVisualInterface instance;
	return instance;
}

void JoinGameMenuVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->usernameTextEntity.draw();
	this->usernameDataBox.draw();

	this->fullAddressTextEntity.draw();
	this->fullAddressDataBox.draw();

	this->joinGameButton.draw();

	this->backButton.draw();
}

void JoinGameMenuVisualInterface::update()
{
	this->backgroundEntity.update();

	this->usernameTextEntity.update();
	this->usernameDataBox.update();

	this->fullAddressTextEntity.update();
	this->fullAddressDataBox.update();

	this->joinGameButton.update();

	this->backButton.update();

	if (this->joinGameButton.anInteractionWillHappen())
	{
		bool userNameOk = true;

		if (this->usernameDataBox.getText().empty())
			userNameOk = false;

		bool fullAddressOk = true;
		int semiColonPos = -1;

		for (int i = 0; i < this->fullAddressDataBox.getText().size(); ++i)
		{
			if (this->fullAddressDataBox.getText()[i] == ':')
			{
				if (semiColonPos != -1)
				{
					fullAddressOk = false;
					break;
				}
				semiColonPos = i;
			}
			else if (!(
				('0' <= this->fullAddressDataBox.getText()[i] && this->fullAddressDataBox.getText()[i] <= '9')
				||
				('a' <= this->fullAddressDataBox.getText()[i] && this->fullAddressDataBox.getText()[i] <= 'z')
				))
				fullAddressOk = false;
		}
		if (semiColonPos == -1)
			fullAddressOk = false;

		if (userNameOk && fullAddressOk)
		{
			std::string username = this->usernameDataBox.getText();

			std::string address = "";
			for (int i = 0; i < semiColonPos; ++i)
				address.push_back(this->fullAddressDataBox.getText()[i]);
			std::string port = "";
			for (int i = semiColonPos + 1; i < this->fullAddressDataBox.getText().size(); ++i)
				port.push_back(this->fullAddressDataBox.getText()[i]);




			InGameVisualInterface::get().setReceivedUsername(username);
			InGameVisualInterface::get().setReceivedServerIP(address);
			InGameVisualInterface::get().setReceivedServerPort(std::stoi(port));




			Game::get().setStatus(Game::Status::IN_GAME);
		}
		else
		{
			if (!userNameOk)
				this->usernameTextEntity.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
			if (!fullAddressOk)
				this->fullAddressTextEntity.setColor(glm::vec3(1.0f, 0.0f, 0.0f));

			AssetManager::get().playSound("errorSound", false, true);
		}
	}
	else if (this->backButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_MULTIPLAYER_MENU);
}

void JoinGameMenuVisualInterface::resetResources()
{
	this->usernameTextEntity.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
	this->fullAddressTextEntity.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}
