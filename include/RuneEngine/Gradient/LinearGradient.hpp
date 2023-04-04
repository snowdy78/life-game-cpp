#pragma once

namespace rn
{
	class LinearGradient : public sf::Drawable, public sf::Transformable, public ClickableObject
	{
		sf::VertexArray color_line = sf::VertexArray{ sf::TrianglesFan, 4 };
		sf::Color color1 = sf::Color::White,
			color2 = sf::Color::White;
		void set_color_to_vertices();
	public:
		explicit LinearGradient(Vec2f size, sf::Color color1, sf::Color color2);

		void setSize(const Vec2f &size);
		Vec2f getSize() const;

		void setColor(size_t id, sf::Color color);
		sf::Color getColor(size_t id) const;

		// t belong from 0 to 1
		sf::Color findColor(float t) const;

		sf::FloatRect getLocalBounds() const;
		sf::FloatRect getGlobalBounds() const;

		bool isIntersected(const Vec2f &p) const override;
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};
}