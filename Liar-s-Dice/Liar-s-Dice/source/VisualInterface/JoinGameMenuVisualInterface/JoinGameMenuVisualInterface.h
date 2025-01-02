#pragma once

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/TextEntity/TextEntity.h"
#include "../../Entity/DataBox/DataBox.h"
#include "../../Entity/Button/Button.h"

class JoinGameMenuVisualInterface : virtual public VisualInterface
{
private:
	JoinGameMenuVisualInterface();
	virtual ~JoinGameMenuVisualInterface();
	JoinGameMenuVisualInterface(const JoinGameMenuVisualInterface& other) = delete;
	JoinGameMenuVisualInterface& operator= (const JoinGameMenuVisualInterface& other) = delete;
	JoinGameMenuVisualInterface(const JoinGameMenuVisualInterface&& other) = delete;
	JoinGameMenuVisualInterface& operator= (const JoinGameMenuVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	TextEntity usernameTextEntity;
	DataBox usernameDataBox;
	TextEntity fullAddressTextEntity;
	DataBox fullAddressDataBox;
	Button joinGameButton;
	Button backButton;

public:
	static JoinGameMenuVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};