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

void AudioManager::RadioShown()
{
	if(m_pAudioPlayer->IsPlaying(AudioType::BgmNormal))
	{
		m_bgmBeforeRadio = AudioType::BgmNormal;
	}
	else
	{
		m_bgmBeforeRadio = AudioType::BgmAlerted;
	}
	m_pAudioPlayer->StopAll();
	m_pAudioPlayer->Play(AudioType::RadioFrequency);
}

void AudioManager::RadioTypeStarted() const
{
	m_pAudioPlayer->Stop(AudioType::RadioFrequency);
}

void AudioManager::RadioTypeEnded() const
{
	m_pAudioPlayer->Play(AudioType::RadioFrequency);
}

void AudioManager::RadioHidden() const
{
	m_pAudioPlayer->StopAll();
	m_pAudioPlayer->Resume(m_bgmBeforeRadio);
}

void AudioManager::AllEnemiesDied() const
{
	m_pAudioPlayer->Stop(AudioType::BgmAlerted);
	m_pAudioPlayer->Play(AudioType::BgmNormal);
}

void AudioManager::SetPitch(const AudioType audioType, const float pitch) const
{
	m_pAudioPlayer->SetPitch(audioType, pitch);
}
