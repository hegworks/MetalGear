#pragma once

class TextRenderer
{
public:
	TextRenderer(Surface* pScreen);
	void DrawText(const string& text, int x, int y, int scale) const;

private:
	const string FONT_SHEET_ADDRESS = "assets/graphics/font.png";
	static constexpr int FRAME_COUNT = 41;
	const int CHAR_SPACING = 2;
	const int LINE_SPACING = 3;

	Surface* m_surfaces[FRAME_COUNT];
	Sprite* m_sprites[FRAME_COUNT];
	Surface* m_pScreen = nullptr;

	int CharToIndex(char c) const;
	int m_frameSize = 0;
};
