#pragma once
#include "RadioAnimationState.h"
#include "RadioEvents.h"
#include "radioState.h"

class ScreenPrinter;
class TextRenderer;

class Radio
{
public:
	Radio(Surface* pScreen, TextRenderer* pFontTextRenderer);
	void Tick(float deltaTime);
	void Draw();
	void Show(int roomNumber);
	void Hide();
	void KeyDown(int glfwkey);
	void KeyUp(int glfwkey);
	bool ReportActive() const { return m_isShowing; }

private:
	Surface* m_pScreen = nullptr;

	Sprite* m_pStaticParts = nullptr;
	Sprite* m_pSend = nullptr;
	Sprite* m_pReceive = nullptr;
	Sprite* m_pBarFull = nullptr;
	Sprite* m_pBarEmpty = nullptr;
	Sprite* m_pTextBox = nullptr;

	TextRenderer* m_pFrequencyTR = nullptr;
	TextRenderer* m_pFontTR = nullptr;

	const int2 m_staticPartsPos = {281,42};
	const int2 m_sendReceivePos = {304,161};
	const int2 m_barPos = {324,100};
	const int2 m_frequencyPos = {483,101};
	const int m_frequencyScale = 3;

	const string m_frequencyPrefix = "120.";

	const int m_barFullFrameCount = 12;

	const float m_frequencyChangeDelayMax = 200;
	const float m_frequencyChangeDelayMin = 20;
	const float m_frequencyChangeDelayStep = 10;
	float m_frequencyChangeDelay = m_frequencyChangeDelayMax;
	float m_frequencyChangeDelayRemaining = 0;

	static constexpr int m_increaseFrequencyGlfwKey = GLFW_KEY_RIGHT;
	static constexpr int m_decreaseFrequencyGlfwKey = GLFW_KEY_LEFT;
	static constexpr int m_sendGlfwKey = GLFW_KEY_UP;
	static constexpr int m_receiveGlfwKey = GLFW_KEY_DOWN;
	static constexpr int m_skipGlfwKey = GLFW_KEY_ENTER;

	bool m_isShowing = false;
	bool m_shouldIncreaseFrequency = false;
	bool m_shouldDecreaseFrequency = false;

	const int2 m_receiveCallFrequency = {8,5}; // 120.85
	int2 m_frequency = m_receiveCallFrequency;

	int m_barFullCurrentFrame = -1;

	const float2 m_textBoxPosStart = {516,396};
	const float2 m_textBoxPosEnd = {235,313};
	const float m_textBoxScaleStart = 0;
	const float m_textBoxScaleEnd = 1;
	const float m_textBoxScaleDuration = 500;
	float2 m_textBoxPos = m_textBoxPosStart;
	float m_textBoxScale = m_textBoxScaleStart;
	float m_textBoxScalePassed = 0;

	const float m_autoBackToReceiveDelay = 500;
	float m_autoBackToReceiveRemaining = m_autoBackToReceiveDelay;

	const float2 m_textPos = {250,325};
	const float m_textAnimationDelay = 50;
	float m_textAnimationDelayRemaining = 0;
	const float m_textScale = 2;

	const int m_receiveCallRoomNumber = 1;
	int m_roomNumber = 0;

	RadioEvents m_radioEvents = RadioEvents::None;
	RadioState m_radioState = RadioState::Receive;

	RadioAnimationState m_textBoxAnimationState = RadioAnimationState::NotStarted;
	RadioAnimationState m_textAnimationState = RadioAnimationState::NotStarted;
	RadioAnimationState m_barAnimationState = RadioAnimationState::NotStarted;

	string m_text = {};
	const string m_sendText = "This is solid snake...\nYour reply, please.";
	const string m_receiveTexts[2] =
	{
		"This is big boss...\nmission\ngain access to\nthe enemy fortress,\nouter heaven.",
		"take action not to be\ndiscovered by\nthe enemy.\n...over"
	};
	const int m_totalReceiveTexts = 2;
	int m_textLastIndex = 0;
	int m_receiveTextsIndex = 0;
	bool m_shownTextOnceOnFrequency = false;

#if _DEBUG
	ScreenPrinter* m_pScreenPrinter = nullptr;
	string RadioAnimationStateToString(RadioAnimationState radioAnimationState);
#endif

	bool CheckFrequencyDelay(float deltaTime);
	void DecreaseFrequency();
	void IncreaseFrequency();
	void PlayTextBoxAnimation(float deltaTime);
	void StartTextAnimation();
	void PlayTextAnimation(const string& referenceText, float deltaTime);
	void WaitForAutoBackToReceive(float deltaTime);
	void SwitchToReceiveState();
	void CheckReceiveFrequency();
};
