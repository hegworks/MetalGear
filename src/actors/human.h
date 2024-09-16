﻿#pragma once

class Human
{
public:
	Human(Surface* screen);
	~Human();
	char* spriteAddress;
	int graphicFrames;
	Sprite* graphic;
	float2 position;
	float speed;
	int animationFrame;

	void Draw() const;
	virtual void Move(int2 direction);
	virtual void Tick(float deltaTime);

protected:
	Surface* screen;
};
