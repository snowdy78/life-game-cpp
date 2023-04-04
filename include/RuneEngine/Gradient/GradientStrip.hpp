#pragma once

namespace rn
{
	class GradientStrip : public sf::Drawable, public sf::Transformable, std::vector<LinearGradient>, public ClickableObject
	{
		using Gradients = vector<LinearGradient>;
		Vec2f size;
		void onTransform();
	public:
		using Gradients::empty;
		GradientStrip(const Vec2f &size, const std::initializer_list<sf::Color> &colors) noexcept;
		
		size_t getGradientCount() const;
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
		void setSize(const Vec2f &Size);
		Vec2f getSize() const;
		sf::Color findColor(float t) const;
		bool isIntersected(const Vec2f &p) const override;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	};
}