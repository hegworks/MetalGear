#pragma once

class Human
{
public:
	Human();
	~Human();
	char* spriteAddress;
	int graphicFrames;
	Sprite* graphic;
	int2 position;
	int speed;
	int animationFrame;

	void Draw(Surface* screen);
	void Move(int2 direction);
};
