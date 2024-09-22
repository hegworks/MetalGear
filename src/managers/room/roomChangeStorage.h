#pragma once
#include "roomChange.h"
#include "src/tile/levelMap/levelMaps.h"

constexpr float RCS_TOP_Y = SCRHEIGHT - 150.0f;
constexpr float RCS_BOTTOM_Y = -50;
constexpr float RCS_LEFT_X = SCRWIDTH - 80.0f;
constexpr float RCS_RIGHT_X = 16.0f;

class RoomChangeStorage
{
public:
	RoomChange roomChanges[TOTAL_LEVEL_MAPS][ROOMCHANGE_TYPE_COUNT] =
	{
		{ // 0
			{ RoomChangeType::RC0, 1, RoomChangePositionType::TOP, { 0, RCS_TOP_Y } },
		},
		{ // 1
			{ RoomChangeType::RC0, 0, RoomChangePositionType::BOTTOM, { 0, RCS_BOTTOM_Y } },
			{ RoomChangeType::RC1, 2, RoomChangePositionType::RIGHT, { RCS_RIGHT_X, 0 } },
			{ RoomChangeType::RC2, 4, RoomChangePositionType::TOP, { 0, RCS_TOP_Y } },
		},
		{ // 2
			{ RoomChangeType::RC0, 1, RoomChangePositionType::LEFT, { RCS_LEFT_X, 0 } },
			{ RoomChangeType::RC1, 3, RoomChangePositionType::RIGHT, { RCS_RIGHT_X, 0 } },
		},
		{ // 3
			{ RoomChangeType::RC0, 2, RoomChangePositionType::LEFT, { RCS_LEFT_X, 0 } },
		},
		{ // 4
			{ RoomChangeType::RC0, 1, RoomChangePositionType::BOTTOM, { 0, RCS_BOTTOM_Y } },
			{ RoomChangeType::RC1, 5, RoomChangePositionType::RIGHT, { RCS_RIGHT_X, 0 } },
			{ RoomChangeType::RC2, 7, RoomChangePositionType::TOP, { 0, RCS_TOP_Y } },
		},
		{ // 5
			{ RoomChangeType::RC0, 4, RoomChangePositionType::LEFT, { RCS_LEFT_X, 0 } },
			{ RoomChangeType::RC1, 6, RoomChangePositionType::TOP, { 0, RCS_TOP_Y } },
			{ RoomChangeType::RC2, -1, RoomChangePositionType::EXCEPTION, { -1, -1 } },
			{ RoomChangeType::RC3, -1, RoomChangePositionType::EXCEPTION, { -1, -1 } },
			{ RoomChangeType::RC4, -1, RoomChangePositionType::EXCEPTION, { -1, -1 } },
		},
		{ // 6
			{ RoomChangeType::RC0, 5, RoomChangePositionType::BOTTOM, { 0, RCS_BOTTOM_Y } },
		},
		{ // 7
			{ RoomChangeType::RC0, 4, RoomChangePositionType::BOTTOM, { 0, RCS_BOTTOM_Y } },
			{ RoomChangeType::RC1, 8, RoomChangePositionType::TOP, { 0, RCS_TOP_Y } },
		},
		{ // 8
			{ RoomChangeType::RC0, 7, RoomChangePositionType::BOTTOM, { 0, RCS_BOTTOM_Y } },
			{ RoomChangeType::RC1, 9, RoomChangePositionType::RIGHT, { RCS_RIGHT_X, 0 } },
		},
		{ // 9
			{ RoomChangeType::RC0, 8, RoomChangePositionType::LEFT, { RCS_LEFT_X, 0 } },
			{ RoomChangeType::RC1, -1, RoomChangePositionType::EXCEPTION, { -1, -1 } },
			{ RoomChangeType::RC2, -1, RoomChangePositionType::EXCEPTION, { -1, -1 } },
			{ RoomChangeType::RC3, -1, RoomChangePositionType::EXCEPTION, { -1, -1 } },
		},
	};
};
