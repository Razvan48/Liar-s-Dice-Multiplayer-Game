#include "JoinGameMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

#include "../../AssetManager/AssetManager.h"

JoinGameMenuVisualInterface::JoinGameMenuVisualInterface()
	: backgroundEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth()
		, WindowManager::get().getWindowHeight()
		, 0.0f, "inputMenuBackgroundTexture")
	, usernameTextEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 3.0f
		, WindowManager::get().getWindowWidth() / 3.0f
		, WindowManager::get().getWindowHeight() / 7.5f, 0.0f, "Username:")
	, usernameDataBox(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 3.0f
		, WindowManager::get().getWindowHeight() / 7.5f
		, 0.0f, "dataBoxTexture", "username")
	, fullAddressTextEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 3.0f
		, WindowManager::get().getWindowHeight() / 7.5f, 0.0f, "Full Address:")
	, fullAddressDataBox(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 3.0f
		, WindowManager::get().getWindowHeight() / 7.5f
		, 0.0f, "dataBoxTexture", "fulladdress")
	, joinGameButton(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 5.0f
		, 0.0f, "Join Game", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, backButton(WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 8.0f
		, WindowManager::get().getWindowHeight() / 12.0f
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

		// aici pot face verificari pe numele de utilizator

		bool fullAddressOk = true;

		// TODO: aici pot face verificari pe adresa completa

		if (userNameOk && fullAddressOk)
			Game::get().setStatus(Game::Status::IN_GAME);
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
