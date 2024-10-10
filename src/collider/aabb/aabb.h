#pragma once

class Aabb
{
public:
	virtual void UpdatePosition(float2 pos) = 0;
#ifdef _PHYSICS_DEBUG
	virtual void Draw(Surface* pScreen, uint color = 0xff0000) const = 0;
#endif
};
