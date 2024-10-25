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
	ESD = 332, // ...Down
	ESL = 333, // ...Left
	ESR = 334, // ...Right
	EPU = 335, // EnemyPatrolUp
	EPD = 336, // ...Down
	EPL = 337, // ...Left
	EPR = 338, // ...Right
	Door = 328,
	Elevator = 329,
	Hide = 339,
};