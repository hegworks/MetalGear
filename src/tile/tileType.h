#pragma once

enum class TileType
{
	Empty = -1,
	Solid = 323,
	RC0 = 324, // RoomChange
	RC1 = 325,
	RC2 = 326,
	RC3 = 327,
	RC4 = 330,
	ESU = 331, // EnemySpawnUp
	ESD = 332,
	ESL = 333,
	ESR = 334,
	EPU = 335, // EnemyPatrolUp
	EPD = 336,
	EPL = 337,
	EPR = 338,
};