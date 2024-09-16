﻿#include "precomp.h"
#include "levelMaps.h"

LevelMaps::LevelMaps()
{
	const int temp[TOTAL_LEVEL_MAPS][LEVELMAP_ROWS][LEVELMAP_COLS] =
	{
	{ // 0-middle
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,150,250,150,151,151,151,151,151,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{51,51,51,51,51,51,51,51,51,51,51,51,51,151,151,151,151,151,151,151,51,51,51,51,51,51,51,51,51,51,51,51}
	},
	{ // 1-down
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,150,150,150,151,151,151,151,151,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,250,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{51,51,51,51,51,51,51,51,51,51,51,51,51,151,151,151,151,151,151,151,51,51,51,51,51,51,51,51,51,51,51,51}
	},
	{ // 2-left
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,250,150,150,151,151,151,151,151,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{51,51,51,51,51,51,51,51,51,51,51,51,51,151,151,151,151,151,151,151,51,51,51,51,51,51,51,51,51,51,51,51}
	},
	{ // 3-right
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,150,150,250,151,151,151,151,151,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{51,51,51,51,51,51,51,51,51,51,51,51,51,151,151,151,151,151,151,151,51,51,51,51,51,51,51,51,51,51,51,51}
	},
	{ // 4-up
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,250,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,150,150,150,151,151,151,151,151,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151,151,151,151,151,151,151,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,51,51,51,51,51,51,51,0,151,151,151,151,151},
	{0,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,3,4,5,6,252,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,53,54,55,56,150,151,151,151,151,151,151,151,151},
	{151,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,103,104,105,106,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,153,154,155,156,150,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{0,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151,151},
	{51,51,51,51,51,51,51,51,51,51,51,51,51,151,151,151,151,151,151,151,51,51,51,51,51,51,51,51,51,51,51,51}
	}
	};

	// Manually copy the temporary array to the member array
	for(int i = 0; i < TOTAL_LEVEL_MAPS; ++i)
	{
		for(int j = 0; j < LEVELMAP_ROWS; ++j)
		{
			for(int k = 0; k < LEVELMAP_COLS; ++k)
			{
				levelMaps[i][j][k] = temp[i][j][k];
			}
		}
	}
}

int** LevelMaps::GetLevelMapPointers(int id)
{
	int** map = new int* [LEVELMAP_ROWS];
	for(int i = 0; i < LEVELMAP_ROWS; ++i)
	{
		map[i] = levelMaps[id][i];
	}
	return map;
}
