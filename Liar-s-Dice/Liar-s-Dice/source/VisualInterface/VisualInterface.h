#pragma once


class VisualInterface
{
protected:


public:
	VisualInterface();
	virtual ~VisualInterface();
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void resetResources() = 0;
};