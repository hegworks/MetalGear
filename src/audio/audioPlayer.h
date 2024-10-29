#pragma once

namespace Audio
{
class Sound;
}

enum class AudioType;
struct AudioData;

/// <summary>
/// this class just initializes audio files and has functions to control them.
///	this class knows nothing about the game itself because it is controlled through audioManager class.
///	this means that no class has direct access to audioPlayer except audioManager
/// </summary>
class AudioPlayer
{
public:
	AudioPlayer();
	~AudioPlayer();
	void Play(AudioType audioType) const;
	void Stop(AudioType audioType) const;
	void Resume(AudioType audioType) const;
	bool IsPlaying(AudioType audioType) const;
	void StopAll() const;
	void SetPitch(AudioType audioType, float pitch) const;

private:
	const int AUDIO_COUNT = 11;
	AudioData* m_audios[11];

	const float BGM_VOLUME = 0.5f;

	Audio::Sound* GetSound(AudioType audioType) const;
};
