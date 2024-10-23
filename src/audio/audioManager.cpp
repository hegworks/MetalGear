#include "precomp.h"
#include "audioManager.h"

#include "audioPlayer.h"
#include "audioType.h"

AudioManager::AudioManager(AudioPlayer* pAudioPlayer)
{
	m_pAudioPlayer = pAudioPlayer;
}

void AudioManager::RoomChanged()
{
	if(m_pAudioPlayer->IsPlaying(AudioType::BgmAlerted))
	{
		m_pAudioPlayer->Stop(AudioType::BgmAlerted);
		m_pAudioPlayer->Play(AudioType::BgmNormal);
	}
}

void AudioManager::EnemyAlerted()
{
	if(m_pAudioPlayer->IsPlaying(AudioType::BgmNormal))
	{
		m_pAudioPlayer->Stop(AudioType::BgmNormal);
		m_pAudioPlayer->Play(AudioType::Alerted);
		m_pAudioPlayer->Play(AudioType::BgmAlerted);
	}
}
