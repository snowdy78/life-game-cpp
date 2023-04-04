#pragma once

namespace rn
{
	template<class T>
	class clip : public sf::Drawable, public sf::Transformable
	{
		sf::RenderTexture rt;
		sf::Sprite spr;
		Vec2f size;
		const T *drawable;
		sf::FloatRect rect;
		void init()
		{
			const Vec2u usize = Vec2u(Vec2f{ floor(size.x), floor(size.y) });
			rt.create(usize.x, usize.y);
			spr.setTexture(rt.getTexture());
		}
		void reTransform()
		{
			if (drawable != nullptr)
			{
				sf::Transform t1;
				rt.clear({ 0, 0, 0, 0 });
				t1.translate(-rect.left, -rect.top + rect.height);
				t1.scale(1.f, -1.f);
				t1 *= drawable->getInverseTransform();
				rt.draw(*drawable, t1);
			}
		}
	public:
		
		explicit clip(const T &object, const Vec2f &size_)
			: size(size_), drawable(&object), rect({}, size)
		{
			init();
			reTransform();
		}
		
		clip() : drawable(nullptr)
		{
			init();
		}

		void setPosition(const Vec2f &position)
		{
			sf::Transformable::setPosition(position);
			reTransform();
		}
		void setPosition(float x, float y)
		{
			Transformable::setPosition(x, y);
			reTransform();
		}

		void setRect(const sf::FloatRect &r)
		{
			rect = r;
			reTransform();
		}
		sf::FloatRect getRect() const
		{
			return rect;
		}


		void setSize(const Vec2f &size_)
		{
			size = size_;
			reTransform();
		}

		Vec2f getSize() const
		{
			return size;
		}

		sf::FloatRect getGlobalBounds() const
		{
			using namespace math_operations;
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