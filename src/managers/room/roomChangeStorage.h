﻿#pragma once
#include "roomChange.h"
#include "src/tile/levelMap/levelMaps.h"

constexpr float RCS_TOP_Y = SCRHEIGHT - 160.0f;
constexpr float RCS_BOTTOM_Y = -60;
constexpr float RCS_LEFT_X = SCRWIDTH - 90.0f;
constexpr float RCS_RIGHT_X = 25.0f;

class RoomChangeStorage
{
public:
	RoomChange roomChanges[TOTAL_LEVEL_MAPS][ROOMCHANGE_TYPE_COUNT] =
	{
		{ // 0
			{{0,			RCS_TOP_Y},		RoomChangeType::RC0, 1, RoomChangePositionType::TOP },
		},
		{ // 1
			{{0,			RCS_BOTTOM_Y},	RoomChangeType::RC0, 0, RoomChangePositionType::BOTTOM		},
			{{RCS_RIGHT_X,	0			},	RoomChangeType::RC1, 2, RoomChangePositionType::RIGHT		},
			{{0,			RCS_TOP_Y	},	RoomChangeType::RC2, 4, RoomChangePositionType::TOP			},
		},
		{ // 2
			{{RCS_LEFT_X,	0			},	RoomChangeType::RC0, 1, RoomChangePositionType::LEFT		},
			{{RCS_RIGHT_X,	0			},	RoomChangeType::RC1, 3, RoomChangePositionType::RIGHT		},
		},
		{ // 3
			{{RCS_LEFT_X,	0			},	RoomChangeType::RC0, 2, RoomChangePositionType::LEFT		},
		},
		{ // 4
			{{0,			RCS_BOTTOM_Y},	RoomChangeType::RC0, 1, RoomChangePositionType::BOTTOM		},
			{{RCS_RIGHT_X,	0			},	RoomChangeType::RC1, 5, RoomChangePositionType::RIGHT		},
			{{0,			RCS_TOP_Y	},	RoomChangeType::RC2, 7, RoomChangePositionType::TOP			},
		},
		{ // 5
			{{ RCS_LEFT_X,	0			},	RoomChangeType::RC0, 4,	RoomChangePositionType::LEFT		},
			{{ 0,			RCS_TOP_Y	},	RoomChangeType::RC1, 6,	RoomChangePositionType::TOP			},
			{{-1,			-1			},	RoomChangeType::RC2, -1,RoomChangePositionType::EXCEPTION	},
			{{-1,			-1			},	RoomChangeType::RC3, -1,RoomChangePositionType::EXCEPTION	},
			{{-1,			-1			},	RoomChangeType::RC4, -1,RoomChangePositionType::EXCEPTION	},
		},
		{ // 6
			{{0,			RCS_BOTTOM_Y},	RoomChangeType::RC0, 5, RoomChangePositionType::BOTTOM		},
		},
		{ // 7
			{{0,			RCS_BOTTOM_Y},	RoomChangeType::RC0, 4, RoomChangePositionType::BOTTOM		},
			{{0,			RCS_TOP_Y},		RoomChangeType::RC1, 8, RoomChangePositionType::TOP			},
		},
		{ // 8
			{{0,			RCS_BOTTOM_Y}, RoomChangeType::RC0, 7, RoomChangePositionType::BOTTOM		},
			{{RCS_RIGHT_X,	0			}, RoomChangeType::RC1, 9, RoomChangePositionType::RIGHT		},
		},
		{ // 9
			{{RCS_LEFT_X,	0			}, RoomChangeType::RC0, 8, RoomChangePositionType::LEFT			},
			{{-1,			-1			}, RoomChangeType::RC1, -1, RoomChangePositionType::EXCEPTION	},
			{{-1,			-1			}, RoomChangeType::RC2, -1, RoomChangePositionType::EXCEPTION	},
			{{-1,			-1			}, RoomChangeType::RC3, -1, RoomChangePositionType::EXCEPTION	},
		},
	};
};
