#pragma once

class TileSet
{
public:
	const char* ADDRESS = "assets/tiles/main-tileset.png";
	const int WIDTH = 32;
	const int HEIGHT = 32;
	const int ROWS = 50;
	const int COLUMNS = 50;

	Surface* GetGraphic() const { return graphic; }

	TileSet();

private:
	Surface* graphic;
};
