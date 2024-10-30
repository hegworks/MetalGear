#pragma once
enum class AnimationState
{
	NotStarted,
	Started,
	Playing,
	Finished,
};

#if _DEBUG
// this is just for debugging purposes and since it is in the _DEBUG block it will not be included in the final build,
// it being a global function is not ideal, but it is the easiest way to convert the enum to a string which is used just for debugging
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
