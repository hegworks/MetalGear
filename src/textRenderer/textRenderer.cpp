#include "precomp.h"
#include "textRenderer.h"

TextRenderer::TextRenderer(Surface* pScreen, const string& fontAddress, const int frameCount, const int charSpacing, const int lineSpacing, int (*CharToIndex)(char)) : m_CharToIndex(CharToIndex)
{
	if(frameCount > MAX_FRAME_COUNT)
	{
		throw exception("frameCount too big: MAX_FRAME_COUNT is less than frameCount");
	}

	m_pScreen = pScreen;
	m_frameCount = frameCount;
	m_charSpacing = charSpacing;
	m_lineSpacing = lineSpacing;

	Surface* fontSurface = new Surface(fontAddress.data());
	m_frameSize = fontSurface->height;
	for(int i = 0; i < m_frameCount; ++i)
	{
		m_pSurfaces[i] = new Surface(m_frameSize, m_frameSize);
		fontSurface->CopyTo(m_pSurfaces[i], -i * m_frameSize, 0);
		m_pSprites[i] = new Sprite(m_pSurfaces[i], 1);

		//m_pSprites[i]->PrintAsText();
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
			const int charIndex = m_CharToIndex(c);
			const int xPos = x + (m_frameSize + m_charSpacing) * scale * (i - lastNewLineIndex);
			const int yPos = y + (m_frameSize + m_lineSpacing) * scale * newLineCount;
			m_pSprites[charIndex]->DrawScaled(xPos, yPos, m_frameSize * scale, m_frameSize * scale, m_pScreen);
		}
	}
}
