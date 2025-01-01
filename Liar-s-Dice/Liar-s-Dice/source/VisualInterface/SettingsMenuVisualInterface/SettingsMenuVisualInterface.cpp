#include "SettingsMenuVisualInterface.h"

#include "../../Game/Game.h"

#include "../../WindowManager/WindowManager.h"

#include "../../AssetManager/AssetManager.h"

SettingsMenuVisualInterface::SettingsMenuVisualInterface()
	: backgroundEntity(WindowManager::get().getWindowWidth() / 2.0f, WindowManager::get().getWindowHeight() / 2.0f, WindowManager::get().getWindowWidth(), WindowManager::get().getWindowHeight(), 0.0f, "settingsMenuBackgroundTexture")
	, soundOnOffTextEntity(WindowManager::get().getWindowWidth() / 2.0f, WindowManager::get().getWindowHeight() / 2.0f, WindowManager::get().getWindowWidth() / 3.0f, WindowManager::get().getWindowHeight() / 7.5f, 0.0f, "Sound: ERROR")
	, soundOnButton(WindowManager::get().getWindowWidth() / 2.0f, WindowManager::get().getWindowHeight() / 3.0f, WindowManager::get().getWindowWidth() / 3.0f, WindowManager::get().getWindowHeight() / 7.5f, 0.0f, "Sound: ON", "buttonTexture", "buttonPressedSound", "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f), "buttonHoveredSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, soundOffButton(WindowManager::get().getWindowWidth() / 2.0f, WindowManager::get().getWindowHeight() / 6.0f, WindowManager::get().getWindowWidth() / 3.0f, WindowManager::get().getWindowHeight() / 7.5f, 0.0f, "Sound: OFF", "buttonTexture", "buttonPressedSound", "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f), "buttonHoveredSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
	, backButton(WindowManager::get().getWindowWidth() / 10.0f, WindowManager::get().getWindowHeight() / 15.0f, WindowManager::get().getWindowWidth() / 8.0f, WindowManager::get().getWindowHeight() / 12.0f, 0.0f, "Back", "buttonTexture", "buttonPressedSound", "hoveredButtonTexture", glm::vec3(1.0f, 1.0f, 1.0f), "buttonHoveredSound", "inactiveButtonTexture", glm::vec3(0.5f, 0.5f, 0.5f))
{
	if (AssetManager::get().getSoundEnabled())
	{
		this->soundOnOffTextEntity.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		this->soundOnOffTextEntity.setText("Sound: ON");

		this->soundOnButton.setStatus(Button::Status::INACTIVE);
		this->soundOffButton.setStatus(Button::Status::RELEASED);
	}
	else
	{
		this->soundOnOffTextEntity.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		this->soundOnOffTextEntity.setText("Sound: OFF");

		this->soundOffButton.setStatus(Button::Status::INACTIVE);
		this->soundOnButton.setStatus(Button::Status::RELEASED);
	}
}

SettingsMenuVisualInterface::~SettingsMenuVisualInterface()
{

}

SettingsMenuVisualInterface& SettingsMenuVisualInterface::get()
{
	static SettingsMenuVisualInterface instance;
	return instance;
}

void SettingsMenuVisualInterface::draw()
{
	this->backgroundEntity.draw();

	this->soundOnOffTextEntity.draw();

	this->soundOnButton.draw();
	this->soundOffButton.draw();

	this->backButton.draw();
}

void SettingsMenuVisualInterface::update()
{
	this->backgroundEntity.update();

	this->soundOnOffTextEntity.update();

	this->soundOnButton.update();
	this->soundOffButton.update();

	this->backButton.update();

	if (this->soundOnButton.anInteractionWillHappen())
	{
		this->soundOnOffTextEntity.setColor(glm::vec3(0.0f, 1.0f, 0.0f));
		this->soundOnOffTextEntity.setText("Sound: ON");
		AssetManager::get().setSoundEnabled(true);

		this->soundOnButton.setStatus(Button::Status::INACTIVE);
		this->soundOffButton.setStatus(Button::Status::RELEASED);
	}
	else if (this->soundOffButton.anInteractionWillHappen())
	{
		this->soundOnOffTextEntity.setColor(glm::vec3(1.0f, 0.0f, 0.0f));
		this->soundOnOffTextEntity.setText("Sound: OFF");
		AssetManager::get().setSoundEnabled(false);

		this->soundOffButton.setStatus(Button::Status::INACTIVE);
		this->soundOnButton.setStatus(Button::Status::RELEASED);
	}
	else if (this->backButton.anInteractionWillHappen())
		Game::get().setStatus(Game::Status::IN_MAIN_MENU);
}

void SettingsMenuVisualInterface::resetResources()
{

}