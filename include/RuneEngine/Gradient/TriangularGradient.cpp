#include "../Engine.hpp"

namespace rn
{
	void TriangularGradient::onTransform()
	{
		for (size_t i = 0; i < getVertexCount(); i++)
		{
			using math::rad;
			vertices[i].position = getPosition() - getOrigin() + length * Vec2f(std::cosf(270 * rad + getRotation()*rad + 360.f / static_cast<float>(getVertexCount()) * static_cast<float>(i) * rad),
			                                                      std::sinf(270 * rad + getRotation()*rad + 360.f / static_cast<float>(getVertexCount()) * static_cast<float>(i) * rad));
		}
	}

	TriangularGradient::TriangularGradient(float length, sf::Color first,
	                                       sf::Color second,
	                                       sf::Color third)
		: vertices(sf::TrianglesFan, 3), length(length)
	{
		const size_t n = getVertexCount();
		std::vector pairs = { &first, &second, &third };
		for (uint8_t i = 0; i < n; i++)
		{
			using math::rad;
			vertices[i].color = *pairs[i];
		}
		onTransform();
	}
	
	size_t TriangularGradient::getVertexCount() const
	{
		return vertices.getVertexCount();
	}

	void TriangularGradient::setColor(uint8_t index, const sf::Color &color)
	{
		vertices[index].color = color;
	}

	void TriangularGradient::setRotation(float angle)
	{
		Transformable::setRotation(angle);
		onTransform();
	}

	void TriangularGradient::rotate(float angle)
	{
		Transformable::rotate(angle);
		onTransform();
	}

	void TriangularGradient::setScale(const Vec2f &scale)
	{
		Transformable::setScale(scale);
		onTransform();
	}

	void TriangularGradient::setScale(float x, float y)
	{
		Transformable::setScale(x, y);
		onTransform();
	}

	void TriangularGradient::scale(const Vec2f &scale)
	{
		Transformable::scale(scale);
		onTransform();
	}

	void TriangularGradient::scale(float x, float y)
	{
		Transformable::scale(x, y);
		onTransform();
	}

	void TriangularGradient::setPosition(const Vec2f &position)
	{
		Transformable::setPosition(position);
		onTransform();
	}

	void TriangularGradient::setPosition(float x, float y)
	{
		Transformable::setPosition(x, y);
		onTransform();
	}

	void TriangularGradient::setOrigin(const Vec2f &origin)
	{
		Transformable::setOrigin(origin);
		onTransform();
	}

	void TriangularGradient::setOrigin(float x, float y)
	{
		Transformable::setOrigin(x, y);
		onTransform();
	}

	void TriangularGradient::move(const Vec2f &Offset)
	{
		Transformable::move(Offset);
		onTransform();
	}

	void TriangularGradient::move(float x, float y)
	{
		Transformable::move(x, y);
		onTransform();
	}
	
	Vec2f TriangularGradient::getPoint(uint8_t index) const
	{
		return vertices[index].position;
	}
	
	sf::Color TriangularGradient::getColor(uint8_t index) const
	{
		return vertices[index].color;
	}

	sf::Color TriangularGradient::findColor(const Vec2f& p)
	{
		using math::length;
		auto &v1 = vertices[0];
		auto &v2 = vertices[1];
		auto &v3 = vertices[2];
		float len1 = length(v1.position - p);
		float len2 = length(v2.position - p);
		float len3 = length(v3.position - p);
		float l = length(v1.position - v2.position);
		float length_color1 = 1 - len1 / l;
		float length_color2 = 1 - len2 / l;
		float length_color3 = 1 - len3 / l;
		Vec3f color1 = Vec3f{ static_cast<float>(v1.color.r), static_cast<float>(v1.color.g), static_cast<float>(v1.color.b) } * length_color1;
		Vec3f color2 = Vec3f{ static_cast<float>(v2.color.r), static_cast<float>(v2.color.g), static_cast<float>(v2.color.b) } * length_color2;
		Vec3f color3 = Vec3f{ static_cast<float>(v3.color.r), static_cast<float>(v3.color.g), static_cast<float>(v3.color.b) } * length_color3;
		return {
			static_cast<sf::Uint8>(floor(color1.x + color2.x + color3.x)),
			static_cast<sf::Uint8>(floor(color1.y + color2.y + color3.y)),
			static_cast<sf::Uint8>(floor(color1.z + color2.z + color3.z))
		};
	}

	bool TriangularGradient::isIntersected(const Vec2f &p) const
	{
		return math::contains(vertices, p);
	}

	void TriangularGradient::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(vertices, states);
	}
}
