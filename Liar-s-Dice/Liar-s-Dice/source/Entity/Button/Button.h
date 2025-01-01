#pragma once

#include "../TextOnBackgroundEntity/TextOnBackgroundEntity.h"

class Button : virtual public TextOnBackgroundEntity
{
public:
	enum class Status
	{
		RELEASED,
		HOVERED,
		INACTIVE,
	};

protected:
	Button::Status status;

	std::string soundNameWhenPressed;

	std::string textureNameWhenHovered;
	glm::vec3 colorWhenHovered;
	std::string soundNameWhenHovered;

	std::string textureNameWhenInactive;
	glm::vec3 colorWhenInactive;

public:
	Button(float centerPosX, float centerPosY, float width, float height, float rotateAngle, const std::string& text, const std::string& textureName
		, const std::string& soundNameWhenPressed, const std::string& textureNameWhenHovered, const glm::vec3& colorWhenHovered, const std::string& soundNameWhenHovered, const std::string& textureNameWhenInactive, const glm::vec3& colorWhenInactive);
	virtual ~Button();

	virtual void draw() override;
	virtual void update() override;

	inline void setStatus(Button::Status status) { this->status = status; }
};

