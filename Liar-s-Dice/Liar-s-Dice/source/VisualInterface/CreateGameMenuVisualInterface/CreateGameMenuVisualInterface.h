#pragma once

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/TextEntity/TextEntity.h"
#include "../../Entity/DataBox/DataBox.h"
#include "../../Entity/Button/Button.h"

class CreateGameMenuVisualInterface : virtual public VisualInterface
{
private:
	CreateGameMenuVisualInterface();
	virtual ~CreateGameMenuVisualInterface();
	CreateGameMenuVisualInterface(const CreateGameMenuVisualInterface& other) = delete;
	CreateGameMenuVisualInterface& operator= (const CreateGameMenuVisualInterface& other) = delete;
	CreateGameMenuVisualInterface(const CreateGameMenuVisualInterface&& other) = delete;
	CreateGameMenuVisualInterface& operator= (const CreateGameMenuVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	TextEntity usernameTextEntity;
	DataBox usernameDataBox;
	TextEntity numberOfDicesTextEntity;
	DataBox numberOfDicesDataBox;
	Button createGameButton;
	Button backButton;

public:
	static CreateGameMenuVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};