#pragma once
#include "roomChangePositionType.h"
#include "roomChangeType.h"

struct RoomChange
{
	RoomChangeType type;
	int nextRoomId;
	RoomChangePositionType positionType;
	float2 newPlayerPos;
};
