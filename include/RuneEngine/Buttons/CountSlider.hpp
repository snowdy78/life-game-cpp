#pragma once

namespace rn
{
	template<class Shape>
	class CountSlider : public sf::Drawable, public sf::Transformable, public ClickableObject
	{
		Shape shape;
		Vec2f endp;
		float l = 0.f;
	public:
		// Position of CountSlider where slider have 0 ratio
		// _Shape - slider shape
		// end_position where slider have ratio 1
		explicit CountSlider(Shape &&_Shape, const Vec2f &end_position) : shape(std::move(_Shape)), endp(end_position) {}
		CountSlider() = default;
		void setShape(Shape &&shape_)
		{
			shape = std::move(shape_);
			slide(l);
		}
		void slide(float k)
		{
			using namespace math_operations;
			k = std::clamp(k, 0.f, 1.f);
			float length = math::length(endp - getPosition()); // shape size
			l = k;
			shape.setPosition(getPosition() + k * length * direction());
		}
		void setPosition(const Vec2f &position)
		{
			Transformable::setPosition(position);
			slide(l);
		}
		void setPosition(float x, float y)
		{
			Transformable::setPosition(x, y);
			slide(l);
		}
		void setEndPosition(const Vec2f &position)
		{
			endp = position;
			slide(l);
		}
		void setEndPosition(float x, float y)
		{
			endp = {x, y};
			slide(l);
		}
		const Vec2f &getEndPosition() const
		{
			return endp;
		}
		const float &coefficient() const
		{
			return l;
		}

		const Shape &getShape() const
		{
			return shape;
		}

		float getRatio(const Vec2f &position) const
		{
			using math::length, math::nearest, math::norm;
			Vec2f N;
			try
			{
				const Vec2f &p1 = getPosition();
				const Vec2f &p2 = endp;
				N = nearest(position, p1, p2);
				if (!(N.y >= p1.y and N.y <= p2.y and N.x >= p1.x and N.x <= p2.x))
				{
					float l1 = length(position - p1);
					float l2 = length(position - p2);
					N = l1 < l2 ? p1 : p2;
				}
			} catch(math::MathDivision &) // {position, N} - line is parallel to {shape.position, endp} line
			{
				N = position;
			}
			float len = length(N - getPosition()) / length(endp - getPosition());
			return len;
		}
		float getRatio(float x, float y) const
		{
			return getRatio(Vec2f(x, y));
		}
		
		bool isIntersected(const Vec2f& p) const override
		{
			return math::contains(shape, p);
		}
	private:
		Vec2f direction() const
		{
			return math::norm(endp - getPosition());
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			target.draw(shape, states);
		}
	};
}