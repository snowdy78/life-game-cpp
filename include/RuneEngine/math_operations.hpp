#pragma once



namespace rn
{
	namespace math_operations
	{
		template<typename T>
		Vec2<T> operator*(const Vec2<T> &l, const Vec2<T> &r)
		{
			return Vec2<T>(l.x * r.x, l.y * r.y);
		}
		template<typename T>
		Vec2<T> operator/(const Vec2<T> &l, const Vec2<T> &r)
		{
			return Vec2<T>(l.x / r.x, l.y / r.y);
		}
		template<class T>
		Vec2<T> operator+(const Vec2<T> &left, const T &right)
		{
			return Vec2<T>(left.x + right, left.y + right);
		}

		template<class T>
		Vec2<T> &operator+=(Vec2<T> &left, const T &right)
		{
			left = left + right;
			return left;
		}

		template<class T>
		Vec2<T> operator-(const Vec2<T> &left, const T &right)
		{
			return Vec2<T>(left.x - right, left.y - right);
		}

		template<class T>
		Vec2<T> &operator-=(Vec2<T> &left, const T &right)
		{
			left = left - right;
			return left;
		}
	}
}