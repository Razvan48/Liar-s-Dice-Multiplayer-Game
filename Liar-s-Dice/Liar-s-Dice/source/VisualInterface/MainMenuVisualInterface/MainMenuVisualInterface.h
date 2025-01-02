#pragma once

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/Button/Button.h"

class MainMenuVisualInterface : virtual public VisualInterface
{
private:
	MainMenuVisualInterface();
	virtual ~MainMenuVisualInterface();
	MainMenuVisualInterface(const MainMenuVisualInterface& other) = delete;
	MainMenuVisualInterface& operator= (const MainMenuVisualInterface& other) = delete;
	MainMenuVisualInterface(const MainMenuVisualInterface&& other) = delete;
	MainMenuVisualInterface& operator= (const MainMenuVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	Button multiplayerButton;
	Button settingsButton;
	Button creditsButton;
	Button exitButton;

public:
	static MainMenuVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};