#pragma once

class TextRenderer
{
public:
	TextRenderer(Surface* pScreen, const string& fontAddress, int frameCount, int charSpacing, int lineSpacing);
	void DrawText(const string& text, int x, int y, int scale) const;

private:
	string FONT_SHEET_ADDRESS = "assets/graphics/font.png";
	int m_frameCount = 0;
	int m_charSpacing = 0;
	int m_lineSpacing = 0;

	const int MAX_FRAME_COUNT = 50;
	Surface* m_pSurfaces[50];
	Sprite* m_pSprites[50];
	Surface* m_pScreen = nullptr;

	int CharToIndex(char c) const;
	int m_frameSize = 0;
};
