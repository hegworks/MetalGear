#pragma once

class Human
{
public:
	Human();
	~Human();
	char* spriteAddress;
	int graphicFrames;
	Sprite* graphic;
	float2 position;
	float speed;
	int animationFrame;

	void Draw(Surface* screen);
	virtual void Move(int2 direction);
	virtual void Tick(float deltaTime);
};
