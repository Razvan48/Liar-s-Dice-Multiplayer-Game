#pragma once

class Entity
{
private:

protected:
	float posCenterX;
	float posCenterY;
	float width;
	float height;
	float rotateAngle;

	bool requestedDeletion;
	bool canBeDrawn;
	bool canBeUpdated;

	bool isInMouseCollision() const;
	bool isInMouseLastPressedCollision() const;

public:
	Entity(float posCenterX, float posCenterY, float width, float height, float rotateAngle);
	virtual ~Entity();

	virtual void draw() = 0;
	virtual void update() = 0;

	inline bool getRequestedDeletion() const { return this->requestedDeletion; }
	inline void setRequestedDeletion(bool requestedDeletion) { this->requestedDeletion = requestedDeletion; }

	inline bool getCanBeDrawn() const { return this->canBeDrawn; }
	inline void setCanBeDrawn(bool canBeDrawn) { this->canBeDrawn = canBeDrawn; }

	inline bool getCanBeUpdated() const { return this->canBeUpdated; }
	inline void setCanBeUpdated(bool canBeUpdated) { this->canBeUpdated = canBeUpdated; }

	inline float getPosCenterX() const { return this->posCenterX; }
	inline float getPosCenterY() const { return this->posCenterY; }
	inline float getRotateAngle() const { return this->rotateAngle; }

	inline void setPosCenterX(float posCenterX) { this->posCenterX = posCenterX; }
	inline void setPosCenterY(float posCenterY) { this->posCenterY = posCenterY; }
	inline void setRotateAngle(float rotateAngle) { this->rotateAngle = rotateAngle; }

	bool isInCompleteMouseCollision() const;
	bool isInCompleteOutsideMouseCollision() const;
	bool anInteractionWillHappen() const;
};

