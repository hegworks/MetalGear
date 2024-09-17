#include "precomp.h"
#include "player.h"

Player::Player(Surface* screen) : Human(screen)
{
	spriteAddress = "assets/graphics/playerSheet.png";
	graphicFrames = 42;
	graphic = new Sprite(new Surface(spriteAddress), graphicFrames);
	graphic->SetFrame(0);
	position = float2(512, 256);
	speed = 0.25f;
	animationFrame = 0;

	tileBoxCollider = new BoxCollider(screen, {32, 32});
}

void Player::Tick(float deltaTime)
{
	HandleInput();
	UpdateColliders();
	UpdatePosition(deltaTime);
	UpdateAnimationState();
	Animate(deltaTime);
}

void Player::HandleInput()
{
	isIdle = false;

	if(GetAsyncKeyState(VK_UP))
	{
		movementDirection = Direction::Up;
	}
	else if(GetAsyncKeyState(VK_DOWN))
	{
		movementDirection = Direction::Down;
	}
	else if(GetAsyncKeyState(VK_LEFT))
	{
		movementDirection = Direction::Left;
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		movementDirection = Direction::Right;
	}
	else
	{
		isIdle = true;
	}
}

void Player::UpdatePosition(float deltaTime)
{
	if(isIdle) return;

	switch(movementDirection)
	{
		case Direction::Up:
			position.y -= speed * deltaTime;
			break;
		case Direction::Down:
			position.y += speed * deltaTime;
			break;
		case Direction::Left:
			position.x -= speed * deltaTime;
			break;
		case Direction::Right:
			position.x += speed * deltaTime;
			break;
	}
}

void Player::UpdateColliders() const
{
	const int2 feet =
	{
		static_cast<int>(position.x) + tileBoxColliderXOffset,
		static_cast<int>(position.y) + tileBoxColliderYOffset
	};
	tileBoxCollider->UpdatePosition(feet);
	tileBoxCollider->Draw(2);
}

void Player::UpdateAnimationState()
{
	if(isIdle) return;

	switch(movementDirection)
	{
		case Direction::Up:
			currentAnimationState = AnimationState::Up;
			break;
		case Direction::Down:
			currentAnimationState = AnimationState::Down;
			break;
		case Direction::Left:
			currentAnimationState = AnimationState::Left;
			break;
		case Direction::Right:
			currentAnimationState = AnimationState::Right;
			break;
	}
}

void Player::Animate(float deltaTime)
{
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
