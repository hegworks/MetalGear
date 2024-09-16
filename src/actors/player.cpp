#include "precomp.h"
#include "player.h"

Player::Player(Surface* screen) : Human(screen)
{
	spriteAddress = "assets/graphics/playerSheet.png";
	graphicFrames = 42;
	graphic = new Sprite(new Surface(spriteAddress), graphicFrames);
	graphic->SetFrame(0);
	position = float2(100, 100);
	speed = 0.25f;
	animationFrame = 0;
}

void Player::Tick(float deltaTime)
{
	if(GetAsyncKeyState(VK_UP))
	{
		position.y -= speed * deltaTime;
		animationFrame = 6;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		position.y += speed * deltaTime;
		animationFrame = 0;
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		position.x -= speed * deltaTime;
		animationFrame = 3;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		position.x += speed * deltaTime;
		animationFrame = 9;
	}
	graphic->SetFrame(animationFrame);
}
