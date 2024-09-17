#pragma once

constexpr char* TILESET_ADDRESS = "assets/tiles/tileset.png";
constexpr int TILESET_TILEWIDTH = 32;
constexpr int TILESET_TILEHEIGHT = 32;
constexpr int TILESET_ROWS = 19;
constexpr int TILESET_COLUMNS = 18;

class TileSet
{
public:
	Surface* GetGraphic() const { return graphic; }

	TileSet();

private:
	Surface* graphic;
};
