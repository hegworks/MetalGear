#pragma once

class Radio
{
public:
	Radio(Surface* pScreen);
	void Tick(float deltaTime);
	void Draw();
	void Show();
	void Hide();
	void KeyDown(int glfwkey);

private:
	Surface* m_pScreen = nullptr;

	Sprite* m_pStaticParts = nullptr;
	Sprite* m_pSend = nullptr;
	Sprite* m_pReceive = nullptr;
	Sprite* m_pBarFull = nullptr;
	Sprite* m_pBarEmpty = nullptr;

	const int2 m_staticPartsPos = {281,42};
	const int2 m_sendReceivePos = {304,161};
	const int2 m_barPos = {324,100};

	const int m_barFullFrameCount = 12;

	static constexpr int m_toggleShowGlfwKey = GLFW_KEY_F4;

	bool m_isShow = false;
	bool m_isSend = false;

	int m_frequency0 = 5;
	int m_frequency1 = 6;

	int m_barFullCurrentFrame = -1;
};
