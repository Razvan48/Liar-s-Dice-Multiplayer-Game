#pragma once

#include "../../Game/Game.h"

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/Button/Button.h"

class InGameVisualInterface : virtual public VisualInterface
{
private:
	InGameVisualInterface();
	virtual ~InGameVisualInterface();
	InGameVisualInterface(const InGameVisualInterface& other) = delete;
	InGameVisualInterface& operator= (const InGameVisualInterface& other) = delete;
	InGameVisualInterface(const InGameVisualInterface&& other) = delete;
	InGameVisualInterface& operator= (const InGameVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	Button backButton;

	Game::Status gameStatusItCameFrom;

public:
	static InGameVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};