#include "precomp.h"
#include "radio.h"

#include "src/audio/audioManager.h"
#include "src/audio/audioType.h"
#include "src/textRenderer/textRenderer.h"
#include "src/tools/mathExtra.h"
#include "src/tools/screenPrinter.h"

/* this function here (not in the scope of the class) in this form (static constexpr), has the best place and form in my opinion.
 * because even though this is in the global scope, it is only in the cpp file, which will not be included in any other file. so encapsulation is still fine.
 * and this is a function which is being passed as an argument to another function (constructor of TextRenderer). so it really needs to be the same across all instances of this class.
 * so memory is also taken care of.
 * we have the same thing but a bit different in the game.h
 */
static constexpr int FrequencyNumbersTextRendererCharToIndex(char c)
{
	if(c >= '0' && c <= '9') return c - '0'; // 0-9
	if(c == '.') return 10;
	throw exception("character not supported");
}

Radio::Radio(Surface* pScreen, TextRenderer* pFontTextRenderer, AudioManager* pAudioManager)
{
	m_pScreen = pScreen;
	m_pAudioManager = pAudioManager;

	m_pStaticParts = new Sprite(new Surface("assets/graphics/radio/radio_static.png"), 1);
	m_pSend = new Sprite(new Surface("assets/graphics/radio/send.png"), 1);
	m_pReceive = new Sprite(new Surface("assets/graphics/radio/receive.png"), 1);
	m_pBarFull = new Sprite(new Surface("assets/graphics/radio/bars_full.png"), m_barTotalFrameCount);
	m_pBarEmpty = new Sprite(new Surface("assets/graphics/radio/bars_empty.png"), 1);
	m_pTextBox = new Sprite(new Surface("assets/graphics/radio/textBox.png"), 1);
	m_pTalk = new Sprite(new Surface("assets/graphics/radio/talk.png"), m_talkAnimationTotalFrameCount);

	m_pFrequencyTR = new TextRenderer(m_pScreen, "assets/graphics/radio/radioNumbers.png", 11, 0, 0, FrequencyNumbersTextRendererCharToIndex);
	m_pFontTR = pFontTextRenderer;

	UpdateFrequencyAudioPitch();

#ifdef _DEBUG
	m_pScreenPrinter = new ScreenPrinter();
#endif
}

void Radio::Tick(float deltaTime)
{
	if(m_isShowing == false) return;

	CheckReceiveFrequency();

	if(m_barAnimationState == AnimationState::Playing || m_barAnimationState == AnimationState::Started)
	{
		PlayBarAnimation(deltaTime);
		return;
	}

	if(m_barAnimationState == AnimationState::Finished)
	{
		StartTextBoxAnimation();
		m_barAnimationState = AnimationState::NotStarted;
	}

	if(m_textBoxAnimationState == AnimationState::Playing || m_textBoxAnimationState == AnimationState::Started)
	{
		PlayTextBoxAnimation(deltaTime);
		return;
	}

	if(m_textBoxAnimationState == AnimationState::Finished)
	{
		StartTextAnimation();
		m_textBoxAnimationState = AnimationState::NotStarted;
	}

	if(m_textAnimationState == AnimationState::Started || m_textAnimationState == AnimationState::Playing)
	{
		if(m_radioState == RadioState::Send)
		{
			PlayTextAnimation(m_sendText, deltaTime);
			PlayTalkAnimation(deltaTime);
		}
		else if(m_radioState == RadioState::Receive)
		{
			PlayTextAnimation(m_receiveTexts[m_receiveTextsIndex], deltaTime);
		}
	}

	if(m_radioState == RadioState::Send && m_textAnimationState == AnimationState::Finished)
	{
		WaitForAutoBackToReceive(deltaTime);
	}

	if((m_shouldDecreaseFrequency || m_shouldIncreaseFrequency) &&
	   m_radioState == RadioState::Receive &&
	   m_textAnimationState == AnimationState::NotStarted)
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
	m_pScreenPrinter->Print(m_pScreen, "m text: ", m_text, {0,0});
	m_pScreenPrinter->Print(m_pScreen, "RadioState: ", radioStateStr, {0,10});
	m_pScreenPrinter->Print(m_pScreen, "TextBox AnimationState: ", AnimationStateToString(m_textBoxAnimationState), {0,20});
	m_pScreenPrinter->Print(m_pScreen, "Text AnimationState: ", AnimationStateToString(m_textAnimationState), {0,30});
	m_pScreenPrinter->Print(m_pScreen, "Bar AnimationState: ", AnimationStateToString(m_barAnimationState), {0,40});
	m_pScreenPrinter->Print(m_pScreen, "m auto Back To Receive Remaining: ", m_autoBackToReceiveRemaining, {0,50});
	m_pScreenPrinter->Print(m_pScreen, "m bar Animation Remaining: ", m_barAnimationRemaining, {0,60});
	m_pScreenPrinter->Print(m_pScreen, "m bar Animation Current Frame: ", m_barAnimationCurrentFrame, {0,70});
#endif

	m_pStaticParts->Draw(m_pScreen, m_staticPartsPos.x, m_staticPartsPos.y);
	m_pBarEmpty->Draw(m_pScreen, m_barPos.x, m_barPos.y);

	m_pTalk->Draw(m_pScreen, m_talkPos.x, m_talkPos.y);

	char frequency[40];
	sprintf(frequency, "%s%d%d", m_frequencyPrefix.data(), m_frequency.x, m_frequency.y);
	m_pFrequencyTR->DrawText(frequency, m_frequencyPos.x, m_frequencyPos.y, m_frequencyScale);

	if(m_barAnimationCurrentFrame >= 0)
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

	m_pTextBox->DrawScaled(static_cast<int>(m_textBoxPos.x),
						   static_cast<int>(m_textBoxPos.y),
						   static_cast<int>(static_cast<float>(m_pTextBox->GetWidth()) * m_textBoxScale),
						   static_cast<int>(static_cast<float>(m_pTextBox->GetHeight()) * m_textBoxScale),
						   m_pScreen);

	m_pFontTR->DrawText(m_text, static_cast<int>(m_textPos.x), static_cast<int>(m_textPos.y), m_textScale);
}

void Radio::Show(int roomNumber)
{
	m_roomNumber = roomNumber;
	m_isShowing = true;
	m_pAudioManager->RadioShown();
}

void Radio::Hide()
{
	m_isShowing = false;
	SwitchToReceiveState();
	m_pAudioManager->RadioHidden();
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
			if(m_radioState == RadioState::Receive &&
			   m_textAnimationState != AnimationState::Playing
			   && m_barAnimationState != AnimationState::Playing &&
			   m_textBoxAnimationState != AnimationState::Playing)
			{
				m_radioState = RadioState::Send;
				StartTextBoxAnimation();
			}
			break;
		case m_skipGlfwKey:
			if(m_radioState == RadioState::Send)
			{
				SwitchToReceiveState();
			}
			else if(m_radioState == RadioState::Receive && !m_shownTextOnceOnFrequency &&
					(m_textAnimationState == AnimationState::Playing || m_textAnimationState == AnimationState::Finished))
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
	UpdateFrequencyAudioPitch();
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
	UpdateFrequencyAudioPitch();
}

void Radio::StartTextBoxAnimation()
{
	m_textBoxScale = m_textBoxScaleStart;
	m_textBoxScalePassed = 0;
	m_textBoxAnimationState = AnimationState::Started;
}

void Radio::PlayTextBoxAnimation(float deltaTime)
{
	if(m_textBoxAnimationState == AnimationState::Finished)
	{
		return;
	}

	if(m_textBoxScalePassed >= m_textBoxScaleDuration)
	{
		m_textBoxAnimationState = AnimationState::Finished;
		m_textBoxScalePassed = 0;
		return;
	}

	m_textBoxAnimationState = AnimationState::Playing;

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
	m_textAnimationState = AnimationState::Started;
	m_pAudioManager->RadioTypeStarted();
}

void Radio::PlayTextAnimation(const string& referenceText, float deltaTime)
{
	if(m_textAnimationState == AnimationState::Finished)
	{
		return;
	}

	const int maxIndex = static_cast<int>(referenceText.length());

	if(m_textLastIndex == maxIndex)
	{
		m_textAnimationState = AnimationState::Finished;
		return;
	}

	m_textAnimationState = AnimationState::Playing;

	if(m_textAnimationDelayRemaining > 0)
	{
		m_textAnimationDelayRemaining -= deltaTime;
		return;
	}
	m_textAnimationDelayRemaining = m_textAnimationDelay;

	m_text += referenceText.at(m_textLastIndex);
	m_textLastIndex++;
	if(m_radioTypeSoundCharSkipCount == m_radioTypeSoundSkipTimes)
	{
		m_pAudioManager->Play(AudioType::RadioType);
		m_radioTypeSoundCharSkipCount = 0;
	}
	else
	{
		m_radioTypeSoundCharSkipCount++;
	}
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

	m_barAnimationCurrentFrame = -1;
	m_pBarFull->SetFrame(0);

	m_talkAnimationFrame = 0;
	m_pTalk->SetFrame(m_talkAnimationFrame);

	m_textAnimationState = AnimationState::NotStarted;
	m_textBoxAnimationState = AnimationState::NotStarted;

	m_radioState = RadioState::Receive;
	m_pAudioManager->RadioTypeEnded();
}

void Radio::CheckReceiveFrequency()
{
	if(m_frequency == m_receiveCallFrequency &&
	   m_roomNumber == m_receiveCallRoomNumber &&
	   !m_shownTextOnceOnFrequency &&
	   m_radioState == RadioState::Receive &&
	   m_barAnimationState == AnimationState::NotStarted &&
	   m_textBoxAnimationState == AnimationState::NotStarted &&
	   m_textAnimationState == AnimationState::NotStarted)
	{
		StartBarAnimation();
	}
}

void Radio::StartBarAnimation()
{
	m_barAnimationCurrentFrame = -1;
	m_barAnimationRemaining = 0;
	m_barAnimationState = AnimationState::Started;
}

void Radio::PlayBarAnimation(float deltaTime)
{
	if(m_barAnimationState == AnimationState::Finished)
	{
		return;
	}

	if(m_barAnimationCurrentFrame == m_barTotalFrameCount - 1)
	{
		m_barAnimationState = AnimationState::Finished;
		return;
	}

	m_barAnimationState = AnimationState::Playing;

	if(m_barAnimationRemaining > 0)
	{
		m_barAnimationRemaining -= deltaTime;
		return;
	}
	m_barAnimationRemaining = m_barAnimationDelay;

	m_barAnimationCurrentFrame++;
	if(m_barAnimationCurrentFrame == m_barTotalFrameCount)
	{
		m_barAnimationCurrentFrame = m_barTotalFrameCount - 1;
	}
	m_pBarFull->SetFrame(m_barAnimationCurrentFrame);
}

void Radio::PlayTalkAnimation(float deltaTime)
{
	if(m_talkAnimationRemaining > 0)
	{
		m_talkAnimationRemaining -= deltaTime;
		return;
	}
	m_talkAnimationRemaining = m_talkAnimationDelay;

	m_talkAnimationFrame++;
	if(m_talkAnimationFrame == m_talkAnimationTotalFrameCount)
	{
		m_talkAnimationFrame = 0;
	}
	m_pTalk->SetFrame(m_talkAnimationFrame);
}

void Radio::UpdateFrequencyAudioPitch() const
{
	const float frequency = static_cast<float>(m_frequency.x) * 10.0f + static_cast<float>(m_frequency.y);
	const float pitch = static_cast<float>(map_numbers(m_pitchFrequencyStart, m_pitchFrequencyEnd, m_minPitch, m_maxPitch, frequency));
	m_pAudioManager->SetPitch(AudioType::RadioFrequency, pitch);
}
