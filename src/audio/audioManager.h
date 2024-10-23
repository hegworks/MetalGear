#pragma once

enum class AudioType;
class AudioPlayer;

class AudioManager
{
public:
	AudioManager(AudioPlayer* pAudioPlayer);

	void RoomChanged(int roomNumber) const;
	void EnemyAlerted() const;
	void Play(AudioType audioType) const;
	void GameplayStarted() const;
	void Lost() const;
	void Won() const;

private:
	AudioPlayer* m_pAudioPlayer = nullptr;

	const int CALL_ROOM_NUMBER = 1;
};
