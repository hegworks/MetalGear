#include "precomp.h"
#include "player.h"

Player::Player()
{
	spriteAddress = "assets/graphics/playerSheet.png";
	graphicFrames = 42;
	graphic = new Sprite(new Surface(spriteAddress), graphicFrames);
	graphic->SetFrame(0);
	position = int2(200, 200);
	speed = 10;
	animationFrame = 0;
}

