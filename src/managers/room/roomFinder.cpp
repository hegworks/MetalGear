#include "precomp.h"
#include "roomFinder.h"

RoomFinder::RoomFinder(RoomChangeStorage* roomChangeStorage)
{
	this->roomChangeStorage = roomChangeStorage;
}

RoomChange RoomFinder::FindNextRoom(RoomChangeType roomChangeType) const
{
	return roomChangeStorage->roomChanges[currentLevelId][static_cast<int>(roomChangeType)];
}
