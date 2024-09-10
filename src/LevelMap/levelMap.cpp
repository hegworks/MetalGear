#include "precomp.h"
#include "levelMap.h"

LevelMap::LevelMap(int** matrix, int rowCount, int columnCount)
{
	this->rowCount = rowCount;
	this->columnCount = columnCount;
	this->matrix = matrix;
}
