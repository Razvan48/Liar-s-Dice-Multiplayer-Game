#pragma once

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/TextEntity/TextEntity.h"
#include "../../Entity/Button/Button.h"

class SettingsMenuVisualInterface : virtual public VisualInterface
{
private:
	SettingsMenuVisualInterface();
	virtual ~SettingsMenuVisualInterface();
	SettingsMenuVisualInterface(const SettingsMenuVisualInterface& other) = delete;
	SettingsMenuVisualInterface& operator= (const SettingsMenuVisualInterface& other) = delete;
	SettingsMenuVisualInterface(const SettingsMenuVisualInterface&& other) = delete;
	SettingsMenuVisualInterface& operator= (const SettingsMenuVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	TextEntity soundOnOffTextEntity;
	Button soundOnButton;
	Button soundOffButton;
	Button backButton;

public:
	static SettingsMenuVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};