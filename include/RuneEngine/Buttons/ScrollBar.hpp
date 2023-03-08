#pragma once

namespace rn
{
	template<ScrollType type>
	class ScrollBar : public sf::Transformable, public sf::Drawable, public ClickableObject
	{
		Rect shape;
		Transformable *base = nullptr;
		Vec2f default_position;
		Vec2f size;
		Vec2f bounds;
		float l = 0.f;
	public:

		// Size - full size of Object
		// Bounds - limit of slider

		explicit ScrollBar(float length, Transformable *Base, const Vec2f &Size, const Vec2f &Bounds)
			: base(Base), size(Size), bounds(Bounds)
		{
			if (base != nullptr)
				default_position = Base->getPosition();
			if (type == ScrollType::Vertical)
				shape = Rect(Vec2f{length, slider_size()});
			else
				shape = Rect(Vec2f{slider_size(), length});
			scroll(l);
		}
		void setLength(float length)
		{
			if (type == ScrollType::Vertical)
				shape.setSize(Vec2f{ length, slider_size() });
			else shape.setSize(Vec2f{ slider_size(), length });
		}
		ScrollBar() = default;
		void scroll(float k)
		{
			k = std::clamp(k, 0.f, 1.f);
			if (base != nullptr)
			{
				Vec2f F;
				if (type == ScrollType::Vertical)
				{
					shape.setPosition(Vec2f{0, k * (bounds.y - getSize().y)});
					clampPos();
					F = { 0, k * (size.y - bounds.y) }; // first element position
				}
				else
				{
					shape.setPosition(Vec2f{k * (bounds.x - getSize().x), 0});
					clampPos();
					F = { k * (size.x - bounds.x), 0 }; // first element position
				}
				base->setPosition(default_position - F);
			}
			l = k;
		}
		void smooth_scroll(float k, std::chrono::milliseconds time)
		{
			k = std::clamp(k, 0.f, 1.f);
			if (base != nullptr)
			{
				Vec2f F;
				if (type == ScrollType::Vertical)
				{
					move_to(shape, shape.getPosition(), Vec2f{0, k * (bounds.y - getSize().y)}, time);
					clampPos();
					F = { 0, k * (size.y - bounds.y) }; // first element position
				}
				else
				{
					move_to(shape, shape.getPosition(), Vec2f{k * (bounds.x - getSize().x), 0}, time);
					clampPos();
					F = { k * (size.x - bounds.x), 0 }; // first element position
				}
				base->setPosition(default_position - F);
			}
			l = k;
		}
		float coefficient() const
		{
			return l;
		}
		void setBounds(const Vec2f &Bounds)
		{
			bounds = Bounds;
			scroll(l);
		}
		const Vec2f &getBounds() const
		{
			return bounds;
		}
		void setPosition(const Vec2f &position)
		{
			Transformable::setPosition(position);
			scroll(l);
		}
		void setPosition(float x, float y)
		{
			Transformable::setPosition(x, y);
			scroll(l);
		}
		void move(float offsetX, float offsetY)
		{
			Transformable::move(offsetX, offsetY);
			scroll(l);
		}
		void move(const Vec2f &offset)
		{
			Transformable::move(offset);
			scroll(l);
		}
		void resize(const Vec2f &Size)
		{
			size = Size;
			scroll(l);
		}
		const Vec2f &getScrollPosition() const
		{
			return shape.getPosition();
		}
		sf::FloatRect getScrollGlobalBounds() const
		{
			return shape.getGlobalBounds();
		}
		sf::FloatRect getScrollLocalBounds() const
		{
			return shape.getLocalBounds();
		}
		const Vec2f &getSize() const
		{
			return shape.getSize();
		}
		float getRatio(const Vec2f &position) const
		{
			if (type == ScrollType::Vertical)
				return (position.y - getPosition().y) / (bounds.y - shape.getSize().y);
			return (position.x - getPosition().x) / (bounds.x - shape.getSize().x);
		}
		void setObjectPosition(const Vec2f &position)
		{
			default_position = position;
			scroll(l);
		}
		void setObjectPosition(float x, float y)
		{
			default_position = Vec2f(x, y);
			scroll(l);
		}
		void setObject(Transformable *obj)
		{
			base = obj;
			default_position = base->getPosition();
			scroll(l);
		}
		const Rect &getShape() const
		{
			return shape;
		}
		bool isIntersected(const Vec2f &p) const override
		{
			return math::contains(shape, p);
		}
		sf::FloatRect getGlobalBounds() const
		{
			using namespace math_operations;
			return sf::FloatRect(getPosition() - getOrigin(), Vec2f(bounds) * getScale());
		}
		sf::FloatRect getLocalBounds() const
		{
			using namespace math_operations;
			return sf::FloatRect(getOrigin(), Vec2f(bounds));
		}

	private:
		float slider_size() const
		{
			if (type == ScrollType::Vertical)
				return bounds.y * bounds.y / size.y;
			return bounds.x * bounds.x / size.x;
		}
		void clampPos() 
		{
			shape.setPosition(std::clamp(shape.getPosition().x, getPosition().x, getPosition().x + bounds.x),
							  std::clamp(shape.getPosition().y, getPosition().y, getPosition().y + bounds.y)
			);
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			if (type == ScrollType::Vertical)
			{
				if (shape.getSize().y < bounds.y)
					target.draw(shape, states);
			}
			if (type == ScrollType::Horizontal)
				if (shape.getSize().x < bounds.x)
					target.draw(shape, states);
		}
	};
	
}