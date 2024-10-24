#pragma once
enum class AnimationState
{
	NotStarted,
	Started,
	Playing,
	Finished,
};

#if _DEBUG
inline string AnimationStateToString(AnimationState AnimationState)
{
	switch(AnimationState)
	{
		case AnimationState::NotStarted:
			return "NotStarted";
		case AnimationState::Started:
			return "Started";
		case AnimationState::Playing:
			return "Playing";
		case AnimationState::Finished:
			return "Finished";
		default:
			throw exception("Invalid AnimationState");
	}
}
#endif
