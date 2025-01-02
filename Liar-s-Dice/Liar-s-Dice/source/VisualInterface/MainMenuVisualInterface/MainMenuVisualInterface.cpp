#include "MainMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

MainMenuVisualInterface::MainMenuVisualInterface()
	: backgroundEntity(	WindowManager::get().getWindowWidth() / 2.0f
						, WindowManager::get().getWindowHeight() / 2.0f
						, WindowManager::get().getWindowWidth()
						, WindowManager::get().getWindowHeight(), 0.0f
						, "mainMenuBackgroundTexture")
	, multiplayerButton(	WindowManager::get().getWindowWidth() / 2.0f
							, WindowManager::get().getWindowHeight() / 3.0f
							, WindowManager::get().getWindowWidth() / 3.0f
							, WindowManager::get().getWindowHeight() / 7.5f, 0.0f
							, "Multiplayer", "buttonTexture", "pressedButtonSound", "hoveredButtonTexture"
							, glm::vec3(1.0f, 1.0f, 1.0f), "hoveredButtonSound", "inactiveButtonTexture"
							, glm::vec3(0.5f, 0.5f, 0.5f))
	, settingsButton(	WindowManager::get().getWindowWidth() / 2.0f
						, WindowManager::get().getWindowHeight() / 6.0f
						, WindowManager::get().getWindowWidth() / 3.0f
						, WindowManager::get().getWindowHeight() / 7.5f, 0.0f
						, "Settings", "buttonTexture", "pressedButtonSound", "hoveredButtonTexture"
						, glm::vec3(1.0f, 1.0f, 1.0f), "hoveredButtonSound", "inactiveButtonTexture"
						, glm::vec3(0.5f, 0.5f, 0.5f))
	, exitButton(	WindowManager::get().getWindowWidth() / 10.0f
					, WindowManager::get().getWindowHeight() / 15.0f
					, WindowManager::get().getWindowWidth() / 8.0f
					, WindowManager::get().getWindowHeight() / 12.0f, 0.0f
					, "Exit", "buttonTexture", "pressedButtonSound", "hoveredButtonTexture"
					, glm::vec3(1.0f, 1.0f, 1.0f), "hoveredButtonSound", "inactiveButtonTexture"
					, glm::vec3(0.5f, 0.5f, 0.5f))
{

}

MainMenuVisualInterface::~MainMenuVisualInterface()
{

}

MainMenuVisualInterface& MainMenuVisualInterface::get()
{
	static MainMenuVisualInterface instance;
	return instance;
}

void MainMenuVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->multiplayerButton.draw();
	this->settingsButton.draw();
	this->exitButton.draw();
}

void MainMenuVisualInterface::update()
{
	this->backgroundEntity.update();

	this->multiplayerButton.update();
	this->settingsButton.update();
	this->exitButton.update();

	if (this->multiplayerButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_MULTIPLAYER_MENU);
	else if (this->settingsButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_SETTINGS_MENU);
	else if (this->exitButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::EXITING);
}

void MainMenuVisualInterface::resetResources()
{

}