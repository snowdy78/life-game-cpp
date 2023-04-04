#include "../Engine.hpp"

namespace rn
{
	void clip::init()
	{
		const Vec2u usize = Vec2u(Vec2f{ floor(size.x), floor(size.y) });
		rt.create(usize.x, usize.y);
		spr.setTexture(rt.getTexture());
		rt.clear({ 0, 0, 0, 0 });
	}

	void clip::reTransform()
	{
		if (drawable != nullptr)
		{
			sf::Transform t1;
			t1.translate(-obj_bounds.left, -obj_bounds.top + obj_bounds.height);
			t1.scale(1.f, -1.f);
			rt.draw(*drawable, t1);
			rt.setActive(false);
		}
	}

	clip::clip(const Drawable &object, const Vec2f &size, const sf::FloatRect &bounds)
		: size(size), drawable(&object), obj_bounds(bounds)
	{
		init();
		setPosition(obj_bounds.left, obj_bounds.top);
	}

	clip::clip(const Drawable& object, const Vec2f& size_)
		: size(size_), drawable(&object)
	{
		init();
		reTransform();
	}

	clip::clip(const Drawable& object, const sf::FloatRect& bounds) : size(bounds.width, bounds.top), drawable(&object), obj_bounds(bounds)
	{
		init();
		reTransform();
	}

	clip::clip() : drawable(nullptr)
	{
		init();
	}

	void clip::setPosition(const Vec2f& position)
	{
		Transformable::setPosition(position);
		reTransform();
	}

	void clip::setObjectPosition(const Vec2f& position)
	{
		obj_bounds.left = position.x;
		obj_bounds.top = position.y;
		reTransform();
	}

	void clip::setObjectPosition(float x, float y)
	{
		obj_bounds.left = x;
		obj_bounds.top = y;
		reTransform();
	}

	void clip::setPosition(float x, float y)
	{
		Transformable::setPosition(x, y);
		reTransform();
	}

	void clip::setSize(const Vec2f& size_)
	{
		size = size_;
		reTransform();
	}

	Vec2f clip::getSize() const
	{
		return size;
	}

	sf::FloatRect clip::getGlobalBounds() const
	{
		using namespace math_operations;
		return { getPosition() - getOrigin(), getSize() * getScale() };
	}

	sf::FloatRect clip::getLocalBounds() const
	{
		return { getOrigin(), getSize() };
	}

	void clip::draw(sf::RenderTarget& win, sf::RenderStates st) const
	{
		st.transform *= getTransform();
		win.draw(spr, st);
	}
}
