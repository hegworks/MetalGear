#pragma once

constexpr char* TILESET_ADDRESS = "assets/tiles/tileset.png";
constexpr int TILESET_TILEWIDTH = 32;
constexpr int TILESET_TILEHEIGHT = 32;
constexpr int TILESET_ROWS = 19;
constexpr int TILESET_COLUMNS = 18;

class TileSet
{
public:
	TileSet();
	Surface* GetGraphic() const { return m_graphic; }

private:
	Surface* m_graphic = nullptr;
};
