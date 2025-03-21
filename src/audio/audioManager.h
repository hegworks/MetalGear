﻿#pragma once
#include "audioType.h"

enum class AudioType;
class AudioPlayer;

/// <summary>
/// this class gets called from different classes of the game and acts as a mediator between the game and audioPlayer class.
///	this means that no class has direct access to audioPlayer except audioManager
/// </summary>
class AudioManager
{
public:
	AudioManager(AudioPlayer* pAudioPlayer);

	void Play(AudioType audioType) const;
	void SetPitch(AudioType audioType, float pitch) const;

	// event reports
	void GameplayStarted() const;
	void Lost() const;
	void Won() const;
	void RoomChanged(int roomNumber) const;
	void EnemyAlerted() const;
	void RadioShown();
	void RadioTypeStarted() const;
	void RadioTypeEnded() const;
	void RadioHidden() const;
	void AllEnemiesDied() const;

private:
	AudioPlayer* m_pAudioPlayer = nullptr;

	const int CALL_ROOM_NUMBER = 1;

	AudioType m_bgmBeforeRadio = AudioType::BgmNormal;
};
