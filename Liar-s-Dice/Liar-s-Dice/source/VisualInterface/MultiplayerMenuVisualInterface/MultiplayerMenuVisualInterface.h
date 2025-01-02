#pragma once

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/Button/Button.h"

class MultiplayerMenuVisualInterface : virtual public VisualInterface
{
private:
	MultiplayerMenuVisualInterface();
	virtual ~MultiplayerMenuVisualInterface();
	MultiplayerMenuVisualInterface(const MultiplayerMenuVisualInterface& other) = delete;
	MultiplayerMenuVisualInterface& operator= (const MultiplayerMenuVisualInterface& other) = delete;
	MultiplayerMenuVisualInterface(const MultiplayerMenuVisualInterface&& other) = delete;
	MultiplayerMenuVisualInterface& operator= (const MultiplayerMenuVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	Button createGameButton;
	Button joinGameButton;
	Button backButton;

public:
	static MultiplayerMenuVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};