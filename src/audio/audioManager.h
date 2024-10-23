#pragma once

class AudioPlayer;

class AudioManager
{
public:
	AudioManager(AudioPlayer* pAudioPlayer);

	void RoomChanged();
	void EnemyAlerted();

private:
	AudioPlayer* m_pAudioPlayer = nullptr;
};
