#pragma once

class CircleAabb
{
public:
	CircleAabb(float2 pos, float size);

	void UpdatePosition(float2 pos);
#ifdef _PHYSICS_DEBUG
	void Draw(Surface* pScreen, uint color = 0xff0000) const;
#endif
	//bool IsColliding(const BoxAabb* other) const;
	float2 GetPosition() const { return m_pos; }
	float2 GetRadius() const { return m_radius; }

private:
	float2 m_pos{};
	float m_radius{};
};
