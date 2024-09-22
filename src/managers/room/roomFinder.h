#pragma once
#include "roomChange.h"
#include "roomChangeStorage.h"

class RoomFinder
{
public:
	RoomFinder(RoomChangeStorage* roomChangeStorage);
	RoomChange FindNextRoom(RoomChangeType roomChangeType) const;
	void SetCurrentLevelId(int levelId) { currentLevelId = levelId; }
	int GetCurrentLevelId() const { return currentLevelId; }

private:
	RoomChangeStorage* roomChangeStorage;
	int currentLevelId = 0;
};
