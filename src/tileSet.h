#pragma once

class TileSet
{
public:
	Surface* GetGraphic() const { return graphic; }

	TileSet();

private:
	Surface* graphic;
};
