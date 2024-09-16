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

enum AnimationState
{
	Up = 0,
	Down = 1,
	Left = 2,
	Right = 3,
};

bool isIdle = true;

struct MyAnimation
{
	AnimationState state;
	int startFrame;
	int endFrame;
};


const int animationCount = 4;
const float animationUpdateTime = 100.0f;
float animationUpdateTimer = 0.0f;

AnimationState currentAnimationState = Down;
AnimationState lastAnimationState = Down;

MyAnimation animations[animationCount] = {
	{ Up, 6, 8 },
	{ Down, 0, 2 },
	{ Left, 3, 5 },
	{ Right, 9, 11 },
};

void Player::Tick(float deltaTime)
{
	isIdle = false;
	if(GetAsyncKeyState(VK_UP))
	{
		position.y -= speed * deltaTime;
		currentAnimationState = Up;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		position.y += speed * deltaTime;
		currentAnimationState = Down;
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		position.x -= speed * deltaTime;
		currentAnimationState = Left;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		position.x += speed * deltaTime;
		currentAnimationState = Right;
	}
	else
	{
		isIdle = true;
	}

	if(isIdle)
	{
		graphic->SetFrame(animations[currentAnimationState].startFrame);
		animationUpdateTimer = animationUpdateTime;
		return;
	}

	if(currentAnimationState != lastAnimationState)
	{
		animationFrame = animations[currentAnimationState].startFrame;
		lastAnimationState = currentAnimationState;
	}

	animationUpdateTimer += deltaTime;

	if(animationUpdateTimer > animationUpdateTime)
	{
		animationUpdateTimer = 0.0f;

		animationFrame++;
		if(animationFrame > animations[currentAnimationState].endFrame)
		{
			animationFrame = animations[currentAnimationState].startFrame;
		}
		graphic->SetFrame(animationFrame);
	}
}
