#include "MultiplayerMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

MultiplayerMenuVisualInterface::MultiplayerMenuVisualInterface()
	: backgroundEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth()
		, WindowManager::get().getWindowHeight()
		, 0.0f, "multiplayerMenuBackgroundTexture")
	, createGameButton(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 5.0f
		, 0.0f, "Create Game", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, joinGameButton(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 4.0f
		, WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 5.0f
		, 0.0f, "Join Game", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f), "hoveredButtonSound"
		, "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, backButton(WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 8.0f
		, WindowManager::get().getWindowHeight() / 12.0f
		, 0.0f, "Back", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
{

}

MultiplayerMenuVisualInterface::~MultiplayerMenuVisualInterface()
{

}

MultiplayerMenuVisualInterface& MultiplayerMenuVisualInterface::get()
{
	static MultiplayerMenuVisualInterface instance;
	return instance;
}

void MultiplayerMenuVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->createGameButton.draw();
	this->joinGameButton.draw();

	this->backButton.draw();
}

void MultiplayerMenuVisualInterface::update()
{
	this->backgroundEntity.update();

	this->createGameButton.update();
	this->joinGameButton.update();

	this->backButton.update();

	if (this->createGameButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_CREATE_GAME_MENU);
	else if (this->joinGameButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_JOIN_GAME_MENU);
	else if (this->backButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_MAIN_MENU);
}

void MultiplayerMenuVisualInterface::resetResources()
{

}
