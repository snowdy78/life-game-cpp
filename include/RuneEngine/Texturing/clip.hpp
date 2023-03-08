#pragma once

namespace rn
{
	template<class DrawableType>
	class clip : public sf::Drawable, public sf::Transformable
	{
		sf::RenderTexture rt;
		sf::Sprite spr;
		Vec2f size;
		const DrawableType &drawable;
	public:
		explicit clip(const DrawableType &object, const sf::FloatRect &bounds)
			: drawable(object)
		{
			size = {bounds.width, bounds.height};
			this->setPosition(bounds.left, bounds.top);
		}
		explicit clip(const DrawableType &object, const Vec2f &size_)
			: drawable(object)
		{
			size = size_;
			this->setPosition(object.getPosition());
		}
		clip() = default;
		void setPosition(const Vec2f &position)
		{
			Transformable::setPosition(position);
			const Vec2u usize = Vec2u(Vec2f{ floor(size.x), floor(size.y) });
			rt.create(usize.x, usize.y);
			spr.setTexture(rt.getTexture());
			rt.clear({ 0, 0, 0, 0 });
			sf::Transform clip_transform = getInverseTransform();
			clip_transform.translate(0, size.y);
			clip_transform.scale(1.f, -1.f);
			rt.draw(drawable, clip_transform);
			rt.setActive(false);
		}
		void setPosition(float x, float y)
		{
			setPosition(Vec2f(x, y));
		}
		void setSize(const Vec2f &size_)
		{
			size = size_;
			const Vec2u usize = Vec2u(Vec2f{floor(size.x), floor(size.y)});
			rt.create(usize.x, usize.y);
			spr.setTexture(rt.getTexture());
			rt.clear({ 0, 0, 0, 0 });
			sf::Transform clip_transform = getInverseTransform();
			clip_transform.translate(0, size.y);
			clip_transform.scale(1.f, -1.f);
			rt.draw(drawable, clip_transform);
			rt.setActive(false);
		}
		Vec2f getSize() const { return size; }
		sf::FloatRect getGlobalBounds() const
		{
			return { getPosition() - getOrigin(), getSize() * getScale() };
		}
		sf::FloatRect getLocalBounds() const
		{
			return { getOrigin(), getSize() };
		}
	private:
		void draw(sf::RenderTarget &win, sf::RenderStates st) const override
		{
			st.transform *= getTransform();
			win.draw(spr, st);
		}
	};
}