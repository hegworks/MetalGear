#pragma once
#include "src/collider/aabb/aabb.h"

class CircleAabb : Aabb
{
public:
	CircleAabb(float2 pos, float radius);

	virtual void UpdatePosition(float2 pos);
#ifdef _DEBUG
	virtual void Draw(Surface* pScreen, uint color = 0xff0000) const;
#endif
	bool IsColliding(const CircleAabb* other) const;
	bool IsColliding(float2 point) const;
	float2 GetPos() const { return m_pos; }
	float GetRadius() const { return m_radius; }

private:
	float2 m_pos{};
	float m_radius{};

	float Distance(float2 a, float2 b) const;
};
