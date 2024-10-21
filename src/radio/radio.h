#pragma once

class TextRenderer;

class Radio
{
public:
	Radio(Surface* pScreen);
	void Tick(float deltaTime);
	void Draw();
	void Show();
	void Hide();
	void KeyDown(int glfwkey);
	void KeyUp(int glfwkey);
	bool ReportActive() const { return m_isShow; }

private:
	Surface* m_pScreen = nullptr;

	Sprite* m_pStaticParts = nullptr;
	Sprite* m_pSend = nullptr;
	Sprite* m_pReceive = nullptr;
	Sprite* m_pBarFull = nullptr;
	Sprite* m_pBarEmpty = nullptr;

	TextRenderer* m_pFrequencyTR = nullptr;

	const int2 m_staticPartsPos = {281,42};
	const int2 m_sendReceivePos = {304,161};
	const int2 m_barPos = {324,100};
	const int2 m_frequencyPos = {483,101};

	const string m_frequencyPrefix = "120.";

	const int m_barFullFrameCount = 12;

	const float m_frequencyChangeDelay = 200;
	float m_frequencyChangeDelayRemaining = 0;

	static constexpr int m_increaseFrequencyGlfwKey = GLFW_KEY_RIGHT;
	static constexpr int m_decreaseFrequencyGlfwKey = GLFW_KEY_LEFT;

	bool m_isShow = false;
	bool m_isSend = false;
	bool m_shouldIncreaseFrequency = false;
	bool m_shouldDecreaseFrequency = false;

	int m_frequency0 = 5;
	int m_frequency1 = 6;

	int m_barFullCurrentFrame = -1;

	bool CheckFrequencyDelay(float deltaTime);
	void DecreaseFrequency();
	void IncreaseFrequency();
};
