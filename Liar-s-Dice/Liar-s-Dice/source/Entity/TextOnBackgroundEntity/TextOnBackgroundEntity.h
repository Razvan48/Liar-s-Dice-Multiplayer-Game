#pragma once


#include <string>

#include "../TextEntity/TextEntity.h"
#include "../TexturableEntity/TexturableEntity.h"


class TextOnBackgroundEntity : virtual public TextEntity, virtual public TexturableEntity
{
protected:


public:
	TextOnBackgroundEntity(float centerPosX, float centerPosY, float width, float height, float rotateAngle, const std::string& text, const std::string& textureName);
	virtual ~TextOnBackgroundEntity();

	virtual void draw() override;
	virtual void update() override;
};

