#include "Engine.hpp"

namespace rn
{
	
	namespace math
	{
		float around(const float &x, const int n)
		{
			return std::roundf(x * powf(10, static_cast<float>(n))) / powf(10, static_cast<float>(n));
		}

		 bool belongs(const float &x, const float &m, const float &n)
		{
			return x <= m and x >= n or x <= n and x >= m;
		}

		float time()
		{
			return static_cast<float>(clock()) / CLOCKS_PER_SEC;
		}

		MathDivision::MathDivision(const char* message): exception(message)
		{}

		NoIntersection::NoIntersection(const char* message): exception(message)
		{}

		bool contains(const Rect &rect, const Vec2f &p)
		{
			return rect.getGlobalBounds().contains(p);
		}

		bool contains(const sf::FloatRect &rect, const Vec2f &p)
		{
			return rect.contains(p);
		}
		Vec2f nearest(const Vec2f &p, const float &a, const float &b, const float &c)
		{
			float h = powf(a, 2.f) + powf(b, 2.f);
			if (h == 0.f) // when parallel
				throw MathDivision();
			float x = (b * (b * p.x - a * p.y) + a * c) / h;
			float y = (a * (a * p.y - b * p.x) + b * c) / h;
			return { x, y };
		}
		Vec2f nearest(const Vec2f &p, const Vec2f &A, const Vec2f &B)
		{
			// returns the closest point from point p to line AB
			const float &x1 = A.x;
			const float &x2 = B.x;
			const float &y1 = A.y;
			const float &y2 = B.y;
			const float a = y1 - y2;
			const float b = x2 - x1;
			const float c = y1 * x2 - x1 * y2;
			const Vec2f N = nearest(p, a, b, c);
			return N;
		}
		bool contains(const Convex &polygon, const Vec2f &p)
		{ // only for convex
			bool ins = true;
			const Vec2f pp = polygon.getPosition();
			Vec2f p1 = pp + polygon.getPoint(0), p2;
			for (int i = static_cast<int>(polygon.getPointCount()) - 1; i >= 0; i--)
			{
				p2 = pp + polygon.getPoint(i);
				ins = ins && (p1.y - p2.y) * p.x + (p2.x - p1.x) * p.y <= p1.y * p2.x - p1.x * p2.y;
				p1 = p2;
			}
			return ins;
		}
		bool contains(const Circle &circle, const Vec2f &point)
		{
			const float &x = point.x;
			const float &y = point.y;
			const float r = circle.getRadius();
			const float p = circle.getScale().x;
			const float q = circle.getScale().y;
			const Vec2f cor = circle.getOrigin();
			const float x0 = circle.getPosition().x + r * p - cor.x * p;
			const float y0 = circle.getPosition().y + r * q - cor.y * q;
			return powf((x - x0) / p, 2.f) + powf((y - y0) / q, 2.f) <= powf(r, 2.f);
		}
		float length(const Vec2f &v)
		{
			return hypotf(v.x, v.y);
		}

		float length(const float &x, const float &y)
		{
			return hypotf(x, y);
		}

		sf::Color mix(const sf::Color &c1, const sf::Color &c2)
		{
			return sf::Color{ static_cast<sf::Uint8>((c1.r + c2.r) / 2), static_cast<sf::Uint8>((c1.g + c2.g) / 2), static_cast<sf::Uint8>((c1.b + c2.b) / 2), static_cast<sf::Uint8>((c1.a + c2.a) / 2) };
		}
		Vec2f intersect(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3, const Vec2f &p4)
		{ // intersection point of two segments
			// if lines doesn't have intersection return's second position of line one
			const float d = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
			if (d == 0.f) // line1 is parallel line2: true.
				throw NoIntersection();
			const float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / d;
			const float u = ((p1.y - p2.y) * (p1.x - p3.x) - (p1.x - p2.x) * (p1.y - p3.y)) / d;

			if (t > 0.f && t < 1.0f && u > 0.f && u < 1.0f)
			{
				const float px = p1.x + t * (p2.x - p1.x);
				const float py = p1.y + t * (p2.y - p1.y);
				return { px, py };
			}
			return p2;
		}
		float sgn(float x)
		{
			return x == 0.f ? 0.f : x / abs(x);
		}
		float clamp(const float &x, const float &minX, const float maxX)
		{
			return std::min(maxX, std::max(x, minX));
		}
		Vec2f clamp(Vec2f p, sf::FloatRect r)
		{
			return { clamp(p.x, r.left, r.left + r.width), clamp(p.y, r.top, r.top + r.height) };
		}
		Vec2f norm(const Vec2f &v) { return v / length(v); }
	}
}