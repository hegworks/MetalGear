﻿#include "precomp.h"
#include "tileSet.h"

TileSet::TileSet()
{
	m_graphic = new Surface(TILESET_ADDRESS);
}

TileSet::~TileSet()
{
	delete m_graphic;
}
