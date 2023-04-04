#pragma once

namespace rn
{
	class TriangularGradient : public sf::Drawable, public sf::Transformable, public ClickableObject
	{
		sf::VertexArray vertices;
		float length;
		void onTransform();
		
		using Transformable::getPosition;
	public:
		TriangularGradient(float length, sf::Color first, sf::Color second, sf::Color third);

		size_t getVertexCount() const;
		void setColor(uint8_t index, const sf::Color &color);
		void setRotation(float angle);
		void setScale(const Vec2f &scale);
		void setScale(float x, float y);
		void setPosition(const Vec2f &position);
		void setPosition(float x, float y);
		void setOrigin(const Vec2f &origin);
		void setOrigin(float x, float y);
		void rotate(float angle);
		void scale(const Vec2f &scale);
		void scale(float x, float y);
		void move(const Vec2f &Offset);
		void move(float x, float y);
		Vec2f getPoint(uint8_t index) const;
		sf::Color getColor(uint8_t index) const;
		sf::Color findColor(const Vec2f &p);

		bool isIntersected(const Vec2f& p) const override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}