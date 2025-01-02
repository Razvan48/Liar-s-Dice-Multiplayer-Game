#include "CreateGameMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

#include "../../AssetManager/AssetManager.h"

CreateGameMenuVisualInterface::CreateGameMenuVisualInterface()
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
	, createGameButton(9.0f * WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 5.5f
		, WindowManager::get().getWindowHeight() / 10.0f
		, 0.0f, "Create Game", "buttonTexture", "pressedButtonSound"
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

CreateGameMenuVisualInterface::~CreateGameMenuVisualInterface()
{

}

CreateGameMenuVisualInterface& CreateGameMenuVisualInterface::get()
{
	static CreateGameMenuVisualInterface instance;
	return instance;
}

void CreateGameMenuVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->usernameTextEntity.draw();
	this->usernameDataBox.draw();

	this->createGameButton.draw();

	this->backButton.draw();
}

void CreateGameMenuVisualInterface::update()
{
	this->backgroundEntity.update();

	this->usernameTextEntity.update();
	this->usernameDataBox.update();

	this->createGameButton.update();

	this->backButton.update();

	if (this->createGameButton.anInteractionWillHappen())
	{
		bool userNameOk = true;

		// aici pot face verificari pe numele de utilizator

		if (userNameOk)
		{
			std::string username = this->usernameDataBox.getText();

			// TODO: de trimis datele de mai sus catre server apoi

			Game::get().setStatus(Game::Status::IN_GAME);
		}
		else
		{
			this->usernameTextEntity.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
			AssetManager::get().playSound("errorSound", false, true);
		}
	}
	else if (this->backButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_MULTIPLAYER_MENU);
}

void CreateGameMenuVisualInterface::resetResources()
{
	this->usernameTextEntity.setColor(glm::vec3(1.0f, 1.0f, 1.0f));
}
