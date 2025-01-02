#pragma once

#include "../VisualInterface.h"

#include "../../Entity/TexturableEntity/TexturableEntity.h"
#include "../../Entity/Button/Button.h"

class CreditsMenuVisualInterface : virtual public VisualInterface
{
private:
	CreditsMenuVisualInterface();
	virtual ~CreditsMenuVisualInterface();
	CreditsMenuVisualInterface(const CreditsMenuVisualInterface& other) = delete;
	CreditsMenuVisualInterface& operator= (const CreditsMenuVisualInterface& other) = delete;
	CreditsMenuVisualInterface(const CreditsMenuVisualInterface&& other) = delete;
	CreditsMenuVisualInterface& operator= (const CreditsMenuVisualInterface&& other) = delete;

protected:
	TexturableEntity backgroundEntity;
	Button backButton;

public:
	static CreditsMenuVisualInterface& get();
	virtual void draw() override;
	virtual void update() override;
	virtual void resetResources() override;
};