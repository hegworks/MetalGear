#pragma once

class Collider
{
public:
	Collider(Surface* screen);
	~Collider() {}

	virtual void Draw(const int size) {}

protected:
	Surface* screen;
};
