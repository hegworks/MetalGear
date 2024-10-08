#pragma once

class BoxAabb
{
public:
	BoxAabb(float2 pos, float2 size);

	void UpdatePosition(float2 pos);
#ifdef _PHYSICS_DEBUG
	void Draw(Surface* pScreen, uint color = 0xff0000);
#endif
	bool IsColliding(const BoxAabb* other);
	float2 GetPosition() const { return m_pos; }
	float2 GetMin() const { return m_min; }
	float2 GetMax() const { return m_max; }
	float2 GetSize() const { return m_size; }

private:
	float2 m_pos{};
	float2 m_min{};
	float2 m_max{};
	float2 m_size{};
};
