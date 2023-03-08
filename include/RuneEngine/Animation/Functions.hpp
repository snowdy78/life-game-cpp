#pragma once
#include "../variables.hpp"

namespace rn
{
	inline void move_to(sf::Transformable &object, const Vec2f &from, const Vec2f &to, const std::chrono::milliseconds &duration)
	{
		const Vec2f &p1 = from;
		const Vec2f &p2 = to;
		float t = static_cast<float>(duration.count());
		if (t > 0)
		{
			using math::length;
			float s = length(p2 - p1);
			if (length(object.getPosition() - p1) >= s)
			{
				return;
			}
			float v = s * 1000.f / (t * static_cast<float>(FPS));
			object.move(v * math::norm(p2 - p1));
		}
		else
			object.setPosition(p2);
	}
}