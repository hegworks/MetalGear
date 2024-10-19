﻿#include "precomp.h"
#include "textRenderer.h"

TextRenderer::TextRenderer(Surface* pScreen)
{
	m_pScreen = pScreen;

	Surface* fontSurface = new Surface(FONT_SHEET_ADDRESS.data());
	m_frameSize = fontSurface->height;
	for(int i = 0; i < FRAME_COUNT; ++i)
	{
		m_surfaces[i] = new Surface(m_frameSize, m_frameSize);
		fontSurface->CopyTo(m_surfaces[i], -i * m_frameSize, 0);
		m_sprites[i] = new Sprite(m_surfaces[i], 1);

		//m_sprites[i]->PrintAsText();
		//printf("\n");
	}
}

void TextRenderer::DrawText(const string& text, const int x, const int y, const int scale) const
{
	int newLineCount = 0;
	int lastNewLineIndex = 0;
	for(int i = 0; i < text.size(); ++i)
	{
		const char c = text.at(i);
		if(c == '\n')
		{
			newLineCount++;
			lastNewLineIndex = i + 1;
		}
		else
		{
			const int charIndex = CharToIndex(c);
			const int xPos = x + (m_frameSize + CHAR_SPACING) * scale * (i - lastNewLineIndex);
			const int yPos = y + (m_frameSize + LINE_SPACING) * scale * newLineCount;
			m_sprites[charIndex]->DrawScaled(xPos, yPos, m_frameSize * scale, m_frameSize * scale, m_pScreen);
		}
	}
}

int TextRenderer::CharToIndex(char c) const
{
	if(c >= 'a' && c <= 'z') return c - 'a'; // 0-25
	if(c >= 'A' && c <= 'Z') return c - 'A'; // 0-25
	if(c >= '0' && c <= '9') return c - '0' + 26; // 26-35
	if(c == '*') return 35 + 1;
	if(c == '>') return 35 + 2;
	if(c == ',') return 35 + 3;
	if(c == '.') return 35 + 4;
	if(c == ' ') return 35 + 5;
	throw exception("character not supported");
}
