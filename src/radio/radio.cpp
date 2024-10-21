#include "precomp.h"
#include "radio.h"

Radio::Radio(Surface* pScreen)
{
	m_pScreen = pScreen;

	m_pStaticParts = new Sprite(new Surface("assets/graphics/radio/0000_radio_static.png"), 1);
	m_pSend = new Sprite(new Surface("assets/graphics/radio/0000_send.png"), 1);
	m_pReceive = new Sprite(new Surface("assets/graphics/radio/0000_receive.png"), 1);
	m_pBarFull = new Sprite(new Surface("assets/graphics/radio/0000_bars_full.png"), m_barFullFrameCount);
	m_pBarEmpty = new Sprite(new Surface("assets/graphics/radio/0000_bars_empty.png"), 1);
}

void Radio::Tick(float deltaTime)
{
	//TODO
}

void Radio::Draw()
{
	if(m_isShow == false) return;

	m_pScreen->Clear(0);
	m_pStaticParts->Draw(m_pScreen, m_staticPartsPos.x, m_staticPartsPos.y);
	m_pBarEmpty->Draw(m_pScreen, m_barPos.x, m_barPos.y);
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
		case m_toggleShowGlfwKey:
			m_isShow = !m_isShow;
	}
}
