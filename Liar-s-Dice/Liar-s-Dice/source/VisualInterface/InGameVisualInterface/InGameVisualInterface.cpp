#include "InGameVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

InGameVisualInterface::InGameVisualInterface()
	: backgroundEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth()
		, WindowManager::get().getWindowHeight()
		, 0.0f, "inGameBackgroundTexture")
	, backButton(WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 8.0f
		, WindowManager::get().getWindowHeight() / 12.0f
		, 0.0f, "Back", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, gameStatusItCameFrom(Game::Status::NONE)
{

}

InGameVisualInterface::~InGameVisualInterface()
{

}

InGameVisualInterface& InGameVisualInterface::get()
{
	static InGameVisualInterface instance;
	return instance;
}

void InGameVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->backButton.draw();
}

void InGameVisualInterface::update()
{
	this->backgroundEntity.update();

	this->backButton.update();

	if (this->backButton.anInteractionWillHappen())
		Game::get().setStatus(this->gameStatusItCameFrom);
}

void InGameVisualInterface::resetResources()
{
	this->gameStatusItCameFrom = Game::get().getStatus();
}
