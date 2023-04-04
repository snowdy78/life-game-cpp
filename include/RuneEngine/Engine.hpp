#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include <functional>
#include <iterator>
#include <vector>
#include <cmath>
#include <list>
#include <typeinfo>
#include <algorithm>
#include <string>
#include <random>
#include <nlohmann/json.hpp>
#include <exception>
#include <thread>
#include <chrono>


namespace rn
{
	using namespace std::string_literals;
	template <class T> using Vec2 = sf::Vector2<T>;
	template <class T> using Vec3 = sf::Vector3<T>;

	using Vec3i = Vec3<int>;
	using Vec3u = Vec3<unsigned int>;
	using Vec3d = Vec3<double>;
	using Vec3f = Vec3<float>;

	using Vec2i = Vec2<int>;
	using Vec2u = Vec2<unsigned int>;
	using Vec2d = Vec2<double>;
	using Vec2f = Vec2<float>;

	using Rect = sf::RectangleShape;
	using Circle = sf::CircleShape;
	using Json = nlohmann::json;
	using Convex = sf::ConvexShape; // convex polygon
	enum class ScrollType
	{
		Vertical, Horizontal
	};
	class JsonFile;
	class Settings;
	
	class Curve; // Bezier Curve

	class LinearGradient;
	class GradientStrip;
	class TriangularGradient;
	class RadialGradient;

	struct Clickable;
	class ClickableObject;
	template<class T>
	class Matrix;
	class RoundedShape;
	class ShaderTexture;
	class Table;
	class TextBlock;
	struct Button;
	struct random;
	template<class T>
	class clip;
	template<class Shape>
	class CountSlider;
	template<ScrollType type = ScrollType::Vertical>
	class ScrollBar;
	class List;
	class StaticTexture;
	class MonoBehaviour;
	template<class ButtonType>
	class Panels;
	template<class Element>
	class ElementList;
	template<class ButtonT, class Element = ButtonT>
	class ElementWithList;
	namespace math_operations
	{
		template<typename T>
		Vec2<T> operator+(const Vec2<T> &v, const T &c);
		template<typename T>
		Vec2<T> operator-(const Vec2<T> &v, const T &c);
		template<typename T>
		Vec2<T> operator*(const Vec2<T> &l, const Vec2<T> &r);
		template<typename T>
		Vec2<T> operator/(const Vec2<T> &l, const Vec2<T> &r);
	}
	namespace math
	{
		constexpr float pi = 3.14159265f;
		constexpr float rad = pi / 180; // radian
		constexpr float e = 2.71828182f;
		struct MathDivision : std::exception
		{
			MathDivision(const char *message);
			MathDivision() = default;
		};
		struct NoIntersection : std::exception
		{
			NoIntersection(const char *message);
			NoIntersection() = default;
		};
		bool contains(const Rect &rect, const Vec2f &point); // if point in rect, then returns true 
		bool contains(const sf::FloatRect &rect, const Vec2f &point); // ro - left top point of rect
		bool contains(const sf::VertexArray &convex_polygon, const Vec2f &p);
		bool contains(const Convex &polygon, const Vec2f &point);
		bool contains(const Circle &circle, const Vec2f &point);
		Vec2f nearest(const Vec2f &p, const Vec2f &A, const Vec2f &B); // returns the closest point from point p to line AB
		float length(const Vec2f &v);
		float length(const float &x, const float &y = 0);
		float around(const float &x, int n); // rounds to n'th number after the decimal point
		float sgn(float x); // returns a sign of number
		bool belongs(const float &x, const float &m, const float &n);
		Vec2f norm(const Vec2f &v); // normalized vector
		Vec2f nor(const Vec2f &v); // vector normal' 
		sf::Color mix(const sf::Color &c1, const sf::Color &c2);
		float clamp(const float &x, const float &minX, float maxX);
		Vec2f intersect(const Vec2f &p1, const Vec2f &p2, const Vec2f &p3, const Vec2f &p4);
		float getAngle(const Vec2f &, const Vec2f &, const Vec2f &);
		float rot(const Vec2f &);
	}
	

	namespace time
	{
		class Timer;
		class StopWatch;
		class Clock;
	}
	namespace algorithm
	{
		template<class T>
		bool in(const T &value, const std::vector<T> &values);
		template<class T>
		std::vector<T> operator+(const std::vector<T> &u, const std::vector<T> &v);
		template<class T>
		std::vector<T *> operator+(const std::vector<T *> &u, const std::vector<T *> &v);
		template<class T>
		std::vector<T> &operator+=(std::vector<T> &left, const std::vector<T> &right);
	}
	class MenuBranch;
	void move_to(sf::Transformable &object, const Vec2f &from, const Vec2f &to, const std::chrono::milliseconds &duration = std::chrono::milliseconds(0));
}
#include "algorithm.hpp"
#include "math_operations.hpp"
#include "Time/Watch.hpp"
#include "Time/StopWatch.hpp"
#include "Time/Timer.hpp"
#include "MonoBehaviour.hpp"
#include "Texturing/ShaderTexture.hpp"
#include "Matrix.hpp"
#include "Shapes/RoundedRect.hpp"
#include "Shapes/Table.hpp"
#include "Random.hpp"
#include "Files/JsonFile.hpp"
#include "SettingsFile.hpp"
#include "variables.hpp"
#include "MenuBranch.hpp"
#include "Animation/Functions.hpp"
#include "Shapes/TextBlock.hpp"
#include "Shapes/Curve.hpp"
#include "Texturing/clip.hpp"
#include "Texturing/StaticTexture.hpp"
#include "Buttons/Clickable.hpp"
#include "Buttons/button.hpp"
#include "Buttons/CountSlider.hpp"
#include "Buttons/List.hpp"
#include "Gradient/LinearGradient.hpp"
#include "Gradient/TriangularGradient.hpp"
#include "Gradient/GradientStrip.hpp"
#include "Panels.hpp"
#include "Buttons/ElementList.hpp"
#include "Buttons/ElementWithList.hpp"