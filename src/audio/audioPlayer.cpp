#include "precomp.h"
#include "audioPlayer.h"

#include "audioData.h"
#include "audioType.h"

AudioPlayer::AudioPlayer()
{
	m_audios[0] = new AudioData{AudioType::BgmNormal, new Audio::Sound("assets/audio/0/bgm_normal.mp3",Audio::Sound::Type::Music)};
	m_audios[0]->m_sound->setLooping(true);
	m_audios[0]->m_sound->setVolume(BGM_VOLUME);
	m_audios[1] = new AudioData{AudioType::BgmAlerted, new Audio::Sound("assets/audio/0/bgm_alert.mp3",Audio::Sound::Type::Music)};
	m_audios[1]->m_sound->setLooping(true);
	m_audios[1]->m_sound->setVolume(BGM_VOLUME);
	m_audios[2] = new AudioData{AudioType::Alerted, new Audio::Sound("assets/audio/0/alerted.mp3",Audio::Sound::Type::Sound)};
	m_audios[3] = new AudioData{AudioType::BulletHit, new Audio::Sound("assets/audio/0/bulletHit.mp3",Audio::Sound::Type::Sound)};
	m_audios[4] = new AudioData{AudioType::Call, new Audio::Sound("assets/audio/0/call.mp3",Audio::Sound::Type::Sound)};
	m_audios[5] = new AudioData{AudioType::Lose, new Audio::Sound("assets/audio/0/lose.mp3",Audio::Sound::Type::Sound)};
	m_audios[6] = new AudioData{AudioType::PunchHit, new Audio::Sound("assets/audio/0/punchHit.mp3",Audio::Sound::Type::Sound)};
	m_audios[7] = new AudioData{AudioType::Shoot, new Audio::Sound("assets/audio/0/shoot.mp3",Audio::Sound::Type::Sound)};
	m_audios[8] = new AudioData{AudioType::Win, new Audio::Sound("assets/audio/0/win.mp3",Audio::Sound::Type::Sound)};
	m_audios[9] = new AudioData{AudioType::RadioFrequency, new Audio::Sound("assets/audio/0/radioFrequency2.mp3",Audio::Sound::Type::Music)};
	m_audios[9]->m_sound->setLooping(true);
	m_audios[10] = new AudioData{AudioType::RadioType, new Audio::Sound("assets/audio/0/radioType.mp3",Audio::Sound::Type::Sound)};
}

void AudioPlayer::Play(const AudioType audioType) const
{
	GetSound(audioType)->replay();
}

void AudioPlayer::Stop(const AudioType audioType) const
{
	GetSound(audioType)->stop();
}

void AudioPlayer::Resume(const AudioType audioType) const
{
	GetSound(audioType)->play();
}

bool AudioPlayer::IsPlaying(const AudioType audioType) const
{
	return GetSound(audioType)->isPlaying();
}

void AudioPlayer::StopAll() const
{
	for(int i = 0; i < AUDIO_COUNT; ++i)
	{
		m_audios[i]->m_sound->stop();
	}
}

void AudioPlayer::SetPitch(const AudioType audioType, const float pitch) const
{
	GetSound(audioType)->setPitch(pitch);
}

Audio::Sound* AudioPlayer::GetSound(const AudioType audioType) const
{
	for(int i = 0; i < AUDIO_COUNT; ++i)
	{
		if(m_audios[i]->m_audioType == audioType)
		{
			return m_audios[i]->m_sound;
		}
	}
	throw exception("invalid AudioType");
}
