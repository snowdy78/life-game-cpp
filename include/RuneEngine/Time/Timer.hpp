#pragma once
#include "StopWatch.hpp"
#include <chrono>

namespace rn
{
	class Timer : public StopWatch
	{
		std::chrono::nanoseconds t = std::chrono::nanoseconds(0);
	public:
		template<class T>
		explicit Timer(const T &begin_time);
		Timer();
		template<class T>
		void set(const T &begin_time);

		template<class T>
		T time() const;
	};

	template <class T>
	Timer::Timer(const T& begin_time)
	{
		t = std::chrono::duration_cast<std::chrono::nanoseconds>(begin_time);
	}

	template <class T>
	void Timer::set(const T& begin_time)
	{
		reset();
		t = std::chrono::duration_cast<std::chrono::nanoseconds>(begin_time);
	}

	template <class T>
	T Timer::time() const
	{
		return std::chrono::duration_cast<T>(t - StopWatch::time<std::chrono::nanoseconds>());
	}
}
