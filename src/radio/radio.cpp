#include "precomp.h"
#include "radio.h"

#include "src/textRenderer/textRenderer.h"
#include "src/tools/screenPrinter.h"

static constexpr int FrequencyNumbersTextRendererCharToIndex(char c)
{
	if(c >= '0' && c <= '9') return c - '0'; // 0-9
	if(c == '.') return 10;
	throw exception("character not supported");
}

Radio::Radio(Surface* pScreen, TextRenderer* pFontTextRenderer)
{
	m_pScreen = pScreen;

	m_pStaticParts = new Sprite(new Surface("assets/graphics/radio/0000_radio_static.png"), 1);
	m_pSend = new Sprite(new Surface("assets/graphics/radio/0000_send.png"), 1);
	m_pReceive = new Sprite(new Surface("assets/graphics/radio/0000_receive.png"), 1);
	m_pBarFull = new Sprite(new Surface("assets/graphics/radio/0000_bars_full.png"), m_barFullFrameCount);
	m_pBarEmpty = new Sprite(new Surface("assets/graphics/radio/0000_bars_empty.png"), 1);
	m_pTextBox = new Sprite(new Surface("assets/graphics/radio/textBox.png"), 1);

	m_pFrequencyTR = new TextRenderer(m_pScreen, "assets/graphics/radio/radioNumbers.png", 11, 0, 0, FrequencyNumbersTextRendererCharToIndex);
	m_pFontTR = pFontTextRenderer;

#ifdef _DEBUG
	m_pScreenPrinter = new ScreenPrinter();
#endif

}

void Radio::Tick(float deltaTime)
{
	if(m_isShowing == false) return;

	CheckReceiveFrequency();

	if(m_textBoxAnimationState == RadioAnimationState::Playing || m_textBoxAnimationState == RadioAnimationState::Started)
	{
		PlayTextBoxAnimation(deltaTime);
		return;
	}

	if(m_textBoxAnimationState == RadioAnimationState::Finished)
	{
		StartTextAnimation();
		m_textBoxAnimationState = RadioAnimationState::NotStarted;
	}

	if(m_textAnimationState == RadioAnimationState::Started || m_textAnimationState == RadioAnimationState::Playing)
	{
		if(m_radioState == RadioState::Send)
		{
			PlayTextAnimation(m_sendText, deltaTime);
		}
		else if(m_radioState == RadioState::Receive)
		{
			PlayTextAnimation(m_receiveTexts[m_receiveTextsIndex], deltaTime);
		}
	}

	if(m_radioState == RadioState::Send && m_textAnimationState == RadioAnimationState::Finished)
	{
		WaitForAutoBackToReceive(deltaTime);
	}

	if((m_shouldDecreaseFrequency || m_shouldIncreaseFrequency) &&
	   m_radioState == RadioState::Receive &&
	   m_textAnimationState == RadioAnimationState::NotStarted)
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
	if(m_isShowing == false) return;

	m_pScreen->Clear(0);

#ifdef _DEBUG
	string radioStateStr = "";
	switch(m_radioState)
	{
		case RadioState::Receive:
			radioStateStr = "Receive";
			break;
		case RadioState::Send:
			radioStateStr = "Send";
			break;
		default:
			throw exception("Invalid RadioState");
	}
	m_pScreenPrinter->Print(m_pScreen, "RadioState: ", radioStateStr, {0,0});
	m_pScreenPrinter->Print(m_pScreen, "TextBox AnimationState: ", RadioAnimationStateToString(m_textBoxAnimationState), {0,10});
	m_pScreenPrinter->Print(m_pScreen, "Text AnimationState: ", RadioAnimationStateToString(m_textAnimationState), {0,20});
	m_pScreenPrinter->Print(m_pScreen, "Bar AnimationState: ", RadioAnimationStateToString(m_barAnimationState), {0,30});
	m_pScreenPrinter->Print(m_pScreen, "m text: ", m_text, {0,40});
	m_pScreenPrinter->Print(m_pScreen, "m auto Back To Receive Remaining: ", m_autoBackToReceiveRemaining, {0,50});
#endif

	m_pStaticParts->Draw(m_pScreen, m_staticPartsPos.x, m_staticPartsPos.y);
	m_pBarEmpty->Draw(m_pScreen, m_barPos.x, m_barPos.y);

	char frequency[40];
	sprintf(frequency, "%s%d%d", m_frequencyPrefix.data(), m_frequency.x, m_frequency.y);
	m_pFrequencyTR->DrawText(frequency, m_frequencyPos.x, m_frequencyPos.y, m_frequencyScale);

	if(m_barFullCurrentFrame >= 0)
	{
		m_pBarFull->Draw(m_pScreen, m_barPos.x, m_barPos.y);
	}

	if(m_radioState == RadioState::Send)
	{
		m_pSend->Draw(m_pScreen, m_sendReceivePos.x, m_sendReceivePos.y);
	}
	else if(m_radioState == RadioState::Receive)
	{
		m_pReceive->Draw(m_pScreen, m_sendReceivePos.x, m_sendReceivePos.y);
	}

	m_pTextBox->DrawScaled(m_textBoxPos.x, m_textBoxPos.y, m_pTextBox->GetWidth() * m_textBoxScale, m_pTextBox->GetHeight() * m_textBoxScale, m_pScreen);

	m_pFontTR->DrawText(m_text, m_textPos.x, m_textPos.y, m_textScale);
}

void Radio::Show(int roomNumber)
{
	m_roomNumber = roomNumber;
	m_isShowing = true;
}

void Radio::Hide()
{
	m_isShowing = false;
	SwitchToReceiveState();
}

void Radio::KeyDown(int glfwkey)
{
	if(!m_isShowing) return;

	switch(glfwkey)
	{
		case m_increaseFrequencyGlfwKey:
			m_shouldIncreaseFrequency = true;
			m_frequencyChangeDelayRemaining = 0;
			m_frequencyChangeDelay = m_frequencyChangeDelayMax;
			break;
		case m_decreaseFrequencyGlfwKey:
			m_shouldDecreaseFrequency = true;
			m_frequencyChangeDelayRemaining = 0;
			m_frequencyChangeDelay = m_frequencyChangeDelayMax;
			break;
		case m_sendGlfwKey:
			if(m_radioState == RadioState::Receive && m_textAnimationState != RadioAnimationState::Playing)
			{
				m_radioState = RadioState::Send;
				m_textBoxAnimationState = RadioAnimationState::Started;
			}
			break;
		case m_skipGlfwKey:
			if(m_radioState == RadioState::Send)
			{
				SwitchToReceiveState();
			}
			else if(m_radioState == RadioState::Receive && !m_shownTextOnceOnFrequency)
			{
				m_receiveTextsIndex++;
				if(m_receiveTextsIndex == m_totalReceiveTexts)
				{
					m_shownTextOnceOnFrequency = true;
					m_receiveTextsIndex = 0;
					SwitchToReceiveState();
				}
				else
				{
					StartTextAnimation();
				}
			}
			break;
	}
}

void Radio::KeyUp(int glfwkey)
{
	if(!m_isShowing) return;

	switch(glfwkey)
	{
		case m_increaseFrequencyGlfwKey:
			m_shouldIncreaseFrequency = false;
			m_frequencyChangeDelayRemaining = 0;
			m_frequencyChangeDelay = m_frequencyChangeDelayMax;
			break;
		case m_decreaseFrequencyGlfwKey:
			m_shouldDecreaseFrequency = false;
			m_frequencyChangeDelayRemaining = 0;
			m_frequencyChangeDelay = m_frequencyChangeDelayMax;
			break;
	}
}

#ifdef _DEBUG
string Radio::RadioAnimationStateToString(RadioAnimationState radioAnimationState)
{
	switch(radioAnimationState)
	{
		case RadioAnimationState::NotStarted:
			return "NotStarted";
		case RadioAnimationState::Started:
			return "Started";
		case RadioAnimationState::Playing:
			return "Playing";
		case RadioAnimationState::Finished:
			return "Finished";
		default:
			throw exception("Invalid AnimationState");
	}
}
#endif

bool Radio::CheckFrequencyDelay(float deltaTime)
{
	m_frequencyChangeDelayRemaining -= deltaTime;
	if(m_frequencyChangeDelayRemaining < 0)
	{
		m_frequencyChangeDelay -= m_frequencyChangeDelayStep;
		if(m_frequencyChangeDelay < m_frequencyChangeDelayMin)
		{
			m_frequencyChangeDelay = m_frequencyChangeDelayMin;
		}
		m_frequencyChangeDelayRemaining = m_frequencyChangeDelay;
		return true;
	}
	return false;
}

void Radio::DecreaseFrequency()
{
	m_frequency.y--;
	if(m_frequency.y == -1)
	{
		m_frequency.y = 9;
		m_frequency.x--;
		if(m_frequency.x == -1)
		{
			m_frequency.x = 0;
			m_frequency.y = 0;
		}
	}
	m_shownTextOnceOnFrequency = false;
}

void Radio::IncreaseFrequency()
{
	m_frequency.y++;
	if(m_frequency.y == 10)
	{
		m_frequency.y = 0;
		m_frequency.x++;
		if(m_frequency.x == 10)
		{
			m_frequency.x = 9;
			m_frequency.y = 9;
		}
	}
	m_shownTextOnceOnFrequency = false;
}

void Radio::PlayTextBoxAnimation(float deltaTime)
{
	if(m_textBoxAnimationState == RadioAnimationState::Finished)
	{
		return;
	}

	if(m_textBoxScalePassed >= m_textBoxScaleDuration)
	{
		m_textBoxAnimationState = RadioAnimationState::Finished;
		m_textBoxScalePassed = 0;
		return;
	}

	m_textBoxAnimationState = RadioAnimationState::Playing;

	m_textBoxScale = lerp(m_textBoxScaleStart, m_textBoxScaleEnd, m_textBoxScalePassed / m_textBoxScaleDuration);
	m_textBoxPos.x = lerp(m_textBoxPosStart.x, m_textBoxPosEnd.x, m_textBoxScalePassed / m_textBoxScaleDuration);
	m_textBoxPos.y = lerp(m_textBoxPosStart.y, m_textBoxPosEnd.y, m_textBoxScalePassed / m_textBoxScaleDuration);

	m_textBoxScalePassed += deltaTime;
	if(m_textBoxScalePassed > m_textBoxScaleDuration)
	{
		m_textBoxScalePassed = m_textBoxScaleDuration;

		m_textBoxScale = m_textBoxScaleEnd;
		m_textBoxPos = m_textBoxPosEnd;
	}
}

void Radio::StartTextAnimation()
{
	m_text = "";
	m_textLastIndex = 0;
	m_textAnimationState = RadioAnimationState::Started;
}

void Radio::PlayTextAnimation(const string& referenceText, float deltaTime)
{
	if(m_textAnimationState == RadioAnimationState::Finished)
	{
		return;
	}

	const int maxIndex = referenceText.length();

	if(m_textLastIndex == maxIndex)
	{
		m_textAnimationState = RadioAnimationState::Finished;
		return;
	}

	m_textAnimationState = RadioAnimationState::Playing;

	if(m_textAnimationDelayRemaining > 0)
	{
		m_textAnimationDelayRemaining -= deltaTime;
		return;
	}
	m_textAnimationDelayRemaining = m_textAnimationDelay;

	m_text += referenceText.at(m_textLastIndex);
	m_textLastIndex++;
}

void Radio::WaitForAutoBackToReceive(float deltaTime)
{
	m_autoBackToReceiveRemaining -= deltaTime;
	if(m_autoBackToReceiveRemaining < 0)
	{
		m_autoBackToReceiveRemaining = m_autoBackToReceiveDelay;
		SwitchToReceiveState();
	}
}

void Radio::SwitchToReceiveState()
{
	m_textBoxScale = m_textBoxScaleStart;
	m_textBoxScalePassed = 0;

	m_text = "";
	m_textLastIndex = 0;

	m_autoBackToReceiveRemaining = m_autoBackToReceiveDelay;

	m_textAnimationState = RadioAnimationState::NotStarted;
	m_textBoxAnimationState = RadioAnimationState::NotStarted;

	m_radioState = RadioState::Receive;
}

void Radio::CheckReceiveFrequency()
{
	if(m_frequency == m_receiveCallFrequency &&
	   m_roomNumber == m_receiveCallRoomNumber &&
	   !m_shownTextOnceOnFrequency &&
	   m_radioState == RadioState::Receive &&
	   m_textBoxAnimationState == RadioAnimationState::NotStarted &&
	   m_textAnimationState == RadioAnimationState::NotStarted)
	{
		m_textBoxAnimationState = RadioAnimationState::Started;
	}
}
