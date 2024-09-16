﻿#include "precomp.h"
#include "levelMaps.h"

const int LEVEL_MAPS[TOTAL_LEVEL_MAPS][LevelMap::ROWS][LevelMap::COLS] =
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


int** LevelMaps::GetLevelMapPointers(int id)
{
	int** levelMap = new int* [LevelMap::ROWS];
	for(int i = 0; i < LevelMap::ROWS; i++)
	{
		levelMap[i] = new int[LevelMap::COLS];
		for(int j = 0; j < LevelMap::COLS; j++)
		{
			levelMap[i][j] = LEVEL_MAPS[id][i][j];
		}
	}
	return levelMap;
}
