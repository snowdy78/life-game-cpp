#include "../Engine.hpp"

namespace rn
{
	void GradientStrip::onTransform()
	{
		using math::rad;
		Vec2f gradient_size = { size.x / static_cast<float>(vector::size()), size.y };
		Vec2f position;
		for (auto gradient = begin(); gradient != end(); gradient++)
		{
			gradient->setSize(gradient_size);
			gradient->setScale(getScale());
			gradient->setRotation(getRotation());
			gradient->setOrigin(getOrigin());
			gradient->setPosition(getPosition() + position);
			using namespace math_operations;
			position.x += gradient_size.x * cosf(getRotation() * rad);
			position.y += gradient_size.x * sinf(getRotation() * rad);
		}
	}

	GradientStrip::GradientStrip(const Vec2f &size, const std::initializer_list<sf::Color> &colors) noexcept
		: size(size)
	{
		Vec2f gradient_size = { size.x / static_cast<float>(colors.size()), size.y };
		for (auto color = colors.begin(); color != colors.end(); color++)
		{
			auto color2 = color + 1;
			if (color2 == colors.end())
				color2 = colors.begin();
			LinearGradient gradient = LinearGradient(gradient_size, *color, *color2);
			push_back(gradient);
		}
		onTransform();
	}

	size_t GradientStrip::getGradientCount() const
	{
		return vector::size();
	}

	void GradientStrip::setRotation(float angle)
	{
		Transformable::setRotation(angle);
		onTransform();
	}

	void GradientStrip::setScale(const Vec2f &scale)
	{
		Transformable::setScale(scale);
		onTransform();
	}

	void GradientStrip::setScale(float x, float y)
	{
		Transformable::setScale(x, y);
		onTransform();
	}

	void GradientStrip::setPosition(const Vec2f &position)
	{
		Transformable::setPosition(position);
		onTransform();
	}

	void GradientStrip::setPosition(float x, float y)
	{
		Transformable::setPosition(x, y);
		onTransform();
	}

	void GradientStrip::setOrigin(const Vec2f &origin)
	{
		Transformable::setOrigin(origin);
		onTransform();
	}

	void GradientStrip::setOrigin(float x, float y)
	{
		Transformable::setOrigin(x, y);
		onTransform();
	}

	void GradientStrip::rotate(float angle)
	{
		Transformable::rotate(angle);
		onTransform();
	}

	void GradientStrip::scale(const Vec2f &scale)
	{
		Transformable::scale(scale);
		onTransform();
	}

	void GradientStrip::scale(float x, float y)
	{
		Transformable::scale(x, y);
		onTransform();
	}

	void GradientStrip::move(const Vec2f &Offset)
	{
		Transformable::move(Offset);
		onTransform();
	}

	void GradientStrip::move(float x, float y)
	{
		Transformable::move(x, y);
		onTransform();
	}

	void GradientStrip::setSize(const Vec2f &Size)
	{
		size = Size;
		onTransform();
	}
	
	Vec2f GradientStrip::getSize() const
	{
		return size;
	}

	// t belongs from 0 to 1
	sf::Color GradientStrip::findColor(float t) const
	{
		float t0 = 1.f / static_cast<float>(getGradientCount());
		size_t i = 0;
		while (t > t0)
		{
			t -= t0;
			i++;
		}
		t *= static_cast<float>(getGradientCount());
		auto &gradient = at(i);
		return gradient.findColor(t);
	}

	bool GradientStrip::isIntersected(const Vec2f& p) const
	{
		return std::any_of(begin(), end(), [&p](const LinearGradient &gradient) { return gradient.isIntersected(p); });
	}

	void GradientStrip::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto &i : *this)
		{
			target.draw(i, states);
		}
	}
}
