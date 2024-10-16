#pragma once
#include "src/collider/aabb/aabb.h"

class BoxAabb : Aabb
{
public:
	BoxAabb(float2 pos, float2 size);

	virtual void UpdatePosition(float2 pos);
#ifdef _DEBUG
	virtual void Draw(Surface* pScreen, uint color = 0xff0000) const;
#endif
	bool IsColliding(const BoxAabb* other) const;
	bool IsColliding(float2 point) const;
	float2 GetMin() const { return m_min; }
	float2 GetMax() const { return m_max; }

private:
	float2 m_min{};
	float2 m_max{};
	float2 m_size{};
};
