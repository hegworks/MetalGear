#pragma once

class Collider
{
public:
	Collider(Surface* screen);
	~Collider() {}

	virtual void Draw(const int size) {}
	virtual void Draw(int size, int color = 0xff0000) {}

protected:
	Surface* screen;
};
