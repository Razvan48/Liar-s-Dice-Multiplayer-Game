#include "CreditsMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

CreditsMenuVisualInterface::CreditsMenuVisualInterface()
	: backgroundEntity(WindowManager::get().getWindowWidth() / 2.0f
		, WindowManager::get().getWindowHeight() / 2.0f
		, WindowManager::get().getWindowWidth()
		, WindowManager::get().getWindowHeight()
		, 0.0f, "creditsMenuBackgroundTexture")
	, backButton(9.0f * WindowManager::get().getWindowWidth() / 10.0f
		, WindowManager::get().getWindowHeight() / 15.0f
		, WindowManager::get().getWindowWidth() / 8.0f
		, WindowManager::get().getWindowHeight() / 12.0f
		, 0.0f, "Back", "buttonTexture", "pressedButtonSound"
		, "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f)
		, "hoveredButtonSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
{

}

CreditsMenuVisualInterface::~CreditsMenuVisualInterface()
{

}

CreditsMenuVisualInterface& CreditsMenuVisualInterface::get()
{
	static CreditsMenuVisualInterface instance;
	return instance;
}

void CreditsMenuVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->backButton.draw();
}

void CreditsMenuVisualInterface::update()
{
	this->backgroundEntity.update();

	this->backButton.update();

	if (this->backButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_MAIN_MENU);
}

void CreditsMenuVisualInterface::resetResources()
{

}