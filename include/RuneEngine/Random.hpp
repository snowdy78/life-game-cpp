#pragma once

#include <random>

namespace rn
{
	struct random
	{
	private:
		// plz don't use 'std::srand / std::rand'
		std::random_device rd;
		std::mt19937 generator = std::mt19937(rd());
	public:
		random() = default;
		template<class T>
		static T real(const T &min, const T &max); // returns random real number from min to max 
		template<class T>
		static T integer(const T &min, const T &max); // returns random integer from min to max 
		static bool chance(const float &x); // x belongs to interval from 0.0 to 1.0, for example if x = 0.01f then it have 1% chance to return true
		template<class First, class Last>
		static void shuffle(const First &begin, const Last &end); // shuffling
		template<class Iter, class First, class Last>
		static Iter item(const First &begin, const Last &end);
	};
	template<class T>
	T random::real(const T &min, const T &max)
	{
		random rand;
		std::uniform_real_distribution dist(min, max);
		return dist(rand.generator);
	}
	template<class T>
	T random::integer(const T &min, const T &max)
	{
		random rand;
		std::uniform_int_distribution dist(min, max);
		return dist(rand.generator);
	}
	inline bool random::chance(const float &x)
	{
		return real(0.f, 1.f) < x;
	}
	template <class First, class Last>
	void random::shuffle(const First &begin, const Last &end)
	{
		random rand;
		std::shuffle(begin, end, rand.generator);
	}
	template<class Iter, class First, class Last>
	Iter random::item(const First &begin, const Last &end)
	{
		random rand;
		std::uniform_int_distribution<> dist(0, std::distance(begin, end) - 1);
		std::advance(begin, dist(rand.generator));
		return begin;
	}
}