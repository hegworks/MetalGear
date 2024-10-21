#include "precomp.h"
#include "radio.h"

#include "src/textRenderer/textRenderer.h"

static constexpr int FrequencyNumbersTextRendererCharToIndex(char c)
{
	if(c >= '0' && c <= '9') return c - '0'; // 0-9
	if(c == '.') return 10;
	throw exception("character not supported");
}

Radio::Radio(Surface* pScreen)
{
	m_pScreen = pScreen;

	m_pStaticParts = new Sprite(new Surface("assets/graphics/radio/0000_radio_static.png"), 1);
	m_pSend = new Sprite(new Surface("assets/graphics/radio/0000_send.png"), 1);
	m_pReceive = new Sprite(new Surface("assets/graphics/radio/0000_receive.png"), 1);
	m_pBarFull = new Sprite(new Surface("assets/graphics/radio/0000_bars_full.png"), m_barFullFrameCount);
	m_pBarEmpty = new Sprite(new Surface("assets/graphics/radio/0000_bars_empty.png"), 1);

	m_pFrequencyTR = new TextRenderer(m_pScreen, "assets/graphics/radio/radioNumbers.png", 11, 0, 0, FrequencyNumbersTextRendererCharToIndex);
}

void Radio::Tick(float deltaTime)
{
	if(m_isShow == false) return;

	if(m_shouldDecreaseFrequency || m_shouldIncreaseFrequency)
	{
		if(CheckFrequencyDelay(deltaTime))
		{
			if(m_shouldDecreaseFrequency)
			{
				DecreaseFrequency();
			}
			else if(m_shouldIncreaseFrequency)
			{
				IncreaseFrequency();
			}
		}
	}
}

void Radio::Draw()
{
	if(m_isShow == false) return;

	m_pScreen->Clear(0);
	m_pStaticParts->Draw(m_pScreen, m_staticPartsPos.x, m_staticPartsPos.y);
	m_pBarEmpty->Draw(m_pScreen, m_barPos.x, m_barPos.y);

	char frequency[2];
	sprintf(frequency, "%s%d%d", m_frequencyPrefix.data(), m_frequency1, m_frequency0);
	m_pFrequencyTR->DrawText(frequency, m_frequencyPos.x, m_frequencyPos.y, 3);
	if(m_barFullCurrentFrame >= 0)
	{
		m_pBarFull->Draw(m_pScreen, m_barPos.x, m_barPos.y);
	}
	if(m_isSend)
	{
		m_pSend->Draw(m_pScreen, m_sendReceivePos.x, m_sendReceivePos.y);
	}
	else
	{
		m_pReceive->Draw(m_pScreen, m_sendReceivePos.x, m_sendReceivePos.y);
	}
}

void Radio::Show()
{
	m_isShow = true;
}

void Radio::Hide()
{
	m_isShow = false;
}

void Radio::KeyDown(int glfwkey)
{
	switch(glfwkey)
	{
		case m_increaseFrequencyGlfwKey:
			m_shouldIncreaseFrequency = true;
			m_frequencyChangeDelayRemaining = 0;
			break;
		case m_decreaseFrequencyGlfwKey:
			m_shouldDecreaseFrequency = true;
			m_frequencyChangeDelayRemaining = 0;
			break;
	}
}

void Radio::KeyUp(int glfwkey)
{
	switch(glfwkey)
	{
		case m_increaseFrequencyGlfwKey:
			m_shouldIncreaseFrequency = false;
			m_frequencyChangeDelayRemaining = 0;
			break;
		case m_decreaseFrequencyGlfwKey:
			m_shouldDecreaseFrequency = false;
			m_frequencyChangeDelayRemaining = 0;
			break;
	}
}

bool Radio::CheckFrequencyDelay(float deltaTime)
{
	m_frequencyChangeDelayRemaining -= deltaTime;
	if(m_frequencyChangeDelayRemaining < 0)
	{
		m_frequencyChangeDelayRemaining = m_frequencyChangeDelay;
		return true;
	}
	return false;
}

void Radio::DecreaseFrequency()
{
	m_frequency0--;
	if(m_frequency0 == -1)
	{
		m_frequency0 = 9;
		m_frequency1--;
		if(m_frequency1 == -1)
		{
			m_frequency1 = 0;
			m_frequency0 = 0;
		}
	}
}

void Radio::IncreaseFrequency()
{
	m_frequency0++;
	if(m_frequency0 == 10)
	{
		m_frequency0 = 0;
		m_frequency1++;
		if(m_frequency1 == 10)
		{
			m_frequency1 = 9;
			m_frequency0 = 9;
		}
	}
}
