#include "precomp.h"
#include "audioManager.h"

#include "audioPlayer.h"
#include "audioType.h"

AudioManager::AudioManager(AudioPlayer* pAudioPlayer)
{
	m_pAudioPlayer = pAudioPlayer;
}

void AudioManager::RoomChanged(int roomNumber) const
{
	if(m_pAudioPlayer->IsPlaying(AudioType::BgmAlerted))
	{
		m_pAudioPlayer->Stop(AudioType::BgmAlerted);
		m_pAudioPlayer->Play(AudioType::BgmNormal);
	}
	if(roomNumber == CALL_ROOM_NUMBER)
	{
		m_pAudioPlayer->Play(AudioType::Call);
	}
}

void AudioManager::EnemyAlerted() const
{
	if(m_pAudioPlayer->IsPlaying(AudioType::BgmNormal))
	{
		m_pAudioPlayer->Stop(AudioType::BgmNormal);
		m_pAudioPlayer->Play(AudioType::Alerted);
		m_pAudioPlayer->Play(AudioType::BgmAlerted);
	}
}

void AudioManager::Play(const AudioType audioType) const
{
	m_pAudioPlayer->Play(audioType);
}

void AudioManager::GameplayStarted() const
{
	m_pAudioPlayer->StopAll();
	m_pAudioPlayer->Play(AudioType::BgmNormal);
}

void AudioManager::Lost() const
{
	m_pAudioPlayer->StopAll();
	m_pAudioPlayer->Play(AudioType::Lose);
}

void AudioManager::Won() const
{
	m_pAudioPlayer->StopAll();
	m_pAudioPlayer->Play(AudioType::Win);
}
