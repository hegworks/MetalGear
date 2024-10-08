#pragma once
#include "roomChangePositionType.h"
#include "roomChangeType.h"

struct RoomChange
{
	float2 newPlayerPos;
	RoomChangeType type;
	int nextRoomId;
	RoomChangePositionType positionType;
};
