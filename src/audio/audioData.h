#pragma once
#include <Audio/Sound.hpp>

enum class AudioType;

struct AudioData
{
	AudioType m_audioType = {};
	Audio::Sound* m_sound = nullptr;
};
