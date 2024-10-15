#pragma once

class PixelPerfectCollisionChecker
{
public:
	PixelPerfectCollisionChecker(Surface* screenP);

	bool IsColliding(Sprite* aSprite, Sprite* bSprite, float2 aPos, float2 bPos, int aFrame, int bFrame);
private:
	Surface* m_screenP = nullptr;
};
