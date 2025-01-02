#include "Button.h"

#include "../../Renderer/Renderer.h"
#include "../../InputManager/InputManager.h"
#include "../../AssetManager/AssetManager.h"

Button::Button(float centerPosX, float centerPosY, float width, float height, float rotateAngle, const std::string& text, const std::string& textureName
	, const std::string& soundNameWhenPressed, const std::string& textureNameWhenHovered, const glm::vec3& colorWhenHovered, const std::string& soundNameWhenHovered, const std::string& textureNameWhenInactive, const glm::vec3& colorWhenInactive)
	: Entity(centerPosX, centerPosY, width, height, rotateAngle)
	, TextEntity(centerPosX, centerPosY, width, height, rotateAngle, text)
	, TexturableEntity(centerPosX, centerPosY, width, height, rotateAngle, textureName)
	, TextOnBackgroundEntity(centerPosX, centerPosY, width, height, rotateAngle, text, textureName)
	, status(Button::Status::RELEASED)
	, soundNameWhenPressed(soundNameWhenPressed)
	, textureNameWhenHovered(textureNameWhenHovered), colorWhenHovered(colorWhenHovered)
	, soundNameWhenHovered(soundNameWhenHovered)
	, textureNameWhenInactive(textureNameWhenInactive), colorWhenInactive(colorWhenInactive)
	, originalText(text)
{

}

Button::~Button()
{

}

void Button::draw()
{
	if (!this->canBeDrawn)
		return;

	std::string currentTexture = "";
	if (this->status == Button::Status::RELEASED)
	{
		currentTexture = this->textureName;
	}
	else if (this->status == Button::Status::HOVERED)
	{
		currentTexture = this->textureNameWhenHovered;
	}
	else // if (this->status == Button::Status::INACTIVE)
	{
		currentTexture = this->textureNameWhenInactive;
	}

	Renderer::get().draw( // background
		this->posCenterX,
		this->posCenterY,
		this->width,
		this->height,
		this->rotateAngle,
		currentTexture
	);

	/*
	Renderer::get().drawText( // contur
		this->posCenterX,
		this->posCenterY,
		TextEntity::TEXT_PADDING_0 * this->width,
		TextEntity::TEXT_PADDING_0 * this->height,
		this->rotateAngle,
		this->fontName,
		this->text,
		glm::vec3(0.0f, 0.0f, 0.0f)
	);
	*/

	glm::vec3 currentColor = glm::vec3(1.0f, 1.0f, 1.0f);
	if (this->status == Button::Status::RELEASED)
	{
		currentColor = this->color;
	}
	else if (this->status == Button::Status::HOVERED)
	{
		currentColor = this->colorWhenHovered;
	}
	else // if (this->status == Button::Status::INACTIVE)
	{
		currentColor = this->colorWhenInactive;
	}
	Renderer::get().drawText(
		this->posCenterX,
		this->posCenterY,
		TextEntity::TEXT_PADDING_1 * this->width,
		TextEntity::TEXT_PADDING_1 * this->height,
		this->rotateAngle,
		this->fontName,
		this->text,
		currentColor
	);
}

void Button::update()
{
	if (!this->canBeUpdated)
		return;

	if (this->status == Button::Status::INACTIVE)
		return;

	if (this->isInMouseCollision())
	{
		if (InputManager::get().isLeftMouseButtonReleased()
			&& this->isInMouseLastPressedCollision())
		{
			AssetManager::get().playSound(this->soundNameWhenPressed, false, false);
		}
		else
		{
			if (this->status == Button::Status::RELEASED)
				AssetManager::get().playSound(this->soundNameWhenHovered, false, false);
			this->status = Button::Status::HOVERED;
		}
	}
	else
		this->status = Button::Status::RELEASED;

	if (this->status == Button::Status::HOVERED)
		this->text = ">" + this->originalText;
	else
		this->text = this->originalText;
}

