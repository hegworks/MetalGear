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
	isIdle = false;

	if(GetAsyncKeyState(VK_UP))
	{
		position.y -= speed * deltaTime;
		currentAnimationState = AnimationState::Up;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		position.y += speed * deltaTime;
		currentAnimationState = AnimationState::Down;
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		position.x -= speed * deltaTime;
		currentAnimationState = AnimationState::Left;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		position.x += speed * deltaTime;
		currentAnimationState = AnimationState::Right;
	}
	else
	{
		isIdle = true;
	}

	if(isIdle)
	{
		graphic->SetFrame(animations[static_cast<int>(currentAnimationState)].startFrame);
		animationUpdateTimer = ANIMATION_UPDATE_TIME;
		return;
	}

	if(currentAnimationState != lastAnimationState)
	{
		animationFrame = animations[static_cast<int>(currentAnimationState)].startFrame;
		lastAnimationState = currentAnimationState;
	}

	animationUpdateTimer += deltaTime;

	if(animationUpdateTimer > ANIMATION_UPDATE_TIME)
	{
		animationUpdateTimer = 0.0f;

		animationFrame++;
		if(animationFrame > animations[static_cast<int>(currentAnimationState)].endFrame)
		{
			animationFrame = animations[static_cast<int>(currentAnimationState)].startFrame;
		}

		graphic->SetFrame(animationFrame);
	}
}
