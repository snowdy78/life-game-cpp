#include "../Engine.hpp"

namespace rn
{
	void LinearGradient::set_color_to_vertices()
	{
		using rn::math::mix;
		color_line[0].color = color1;
		color_line[1].color = color2;
		color_line[2].color = color2;
		color_line[3].color = color1;
	}

	LinearGradient::LinearGradient(Vec2f size, sf::Color color1, sf::Color color2)
		: color1(color1), color2(color2)
	{
		setSize(size);
		set_color_to_vertices();
	}

	void LinearGradient::setSize(const Vec2f& size)
	{
		color_line[0].position = Vec2f(0, 0);
		color_line[1].position = Vec2f(size.x, 0);
		color_line[2].position = Vec2f(size.x, size.y);
		color_line[3].position = Vec2f(0, size.y);
	}

	Vec2f LinearGradient::getSize() const
	{
		return color_line[2].position;
	}

	void LinearGradient::setColor(size_t id, sf::Color color)
	{
		if (id == 0)
		{
			color1 = color;
		}
		else color2 = color;
		set_color_to_vertices();
	}

	sf::Color LinearGradient::getColor(size_t id) const
	{
		if (id == 0)
		{
			return color1;
		}
		return color2;
	}

	sf::Color LinearGradient::findColor(float t) const
	{
		sf::Vector3f clr1{ static_cast<float>(color1.r), static_cast<float>(color1.g), static_cast<float>(color1.b) };
		sf::Vector3f clr2{ static_cast<float>(color2.r), static_cast<float>(color2.g), static_cast<float>(color2.b) };
		clr1 *= 1 - t;
		clr2 *= t;
		sf::Color clr = { static_cast<sf::Uint8>(clr1.x + clr2.x), static_cast<sf::Uint8>(clr1.y + clr2.y), static_cast<sf::Uint8>(clr1.z + clr2.z) };
		return clr;
	}

	sf::FloatRect LinearGradient::getLocalBounds() const
	{
		return { getOrigin(), getSize() };
	}

	sf::FloatRect LinearGradient::getGlobalBounds() const
	{
		using namespace rn::math_operations;
		return { getPosition() - getOrigin(), getSize() * getScale() };
	}

	bool LinearGradient::isIntersected(const Vec2f& p) const
	{
		return math::contains(getGlobalBounds(), p);
	}

	void LinearGradient::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(color_line, states);
	}
}
