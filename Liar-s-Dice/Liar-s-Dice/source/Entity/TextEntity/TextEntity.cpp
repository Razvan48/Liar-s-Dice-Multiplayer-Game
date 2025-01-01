#include "TextEntity.h"

#include "../../Renderer/Renderer.h"


TextEntity::TextEntity(float centerPosX, float centerPosY, float width, float height, float rotateAngle, const std::string& text)
	: Entity(centerPosX, centerPosY, width, height, rotateAngle)
	, color(glm::vec3(1.0f, 1.0f, 1.0f)), fontName("arialFont"), text(text)
{

}

TextEntity::~TextEntity()
{

}

const float TextEntity::TEXT_PADDING_0 = 0.95f;
const float TextEntity::TEXT_PADDING_1 = 0.75f;

void TextEntity::draw()
{
	if (!this->canBeDrawn)
		return;

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

	Renderer::get().drawText(
		this->posCenterX,
		this->posCenterY,
		TextEntity::TEXT_PADDING_1 * this->width,
		TextEntity::TEXT_PADDING_1 * this->height,
		this->rotateAngle,
		this->fontName,
		this->text,
		this->color
	);
}

void TextEntity::update()
{
	if (!this->canBeUpdated)
		return;
}

