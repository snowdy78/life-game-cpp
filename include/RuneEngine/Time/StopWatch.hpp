#pragma once

#include "Watch.hpp"
#include <chrono>


namespace rn
{
	class StopWatch : public Watch
	{
		mutable std::chrono::steady_clock::time_point end_ = std::chrono::high_resolution_clock::now();
		std::chrono::steady_clock::time_point start_ = std::chrono::high_resolution_clock::now();
		std::chrono::nanoseconds t = std::chrono::nanoseconds(0);
		bool first_start = true;
	public:
		StopWatch();
		template<class Duration>
		StopWatch(const Duration &begin_time);

		template<class T>
		T time() const;

		void onStart() override;
		void onStop() override;

		void reset();
	};

	template <class Duration>
	StopWatch::StopWatch(const Duration& begin_time)
	{
		t = begin_time;
	}

	template <class T>
	T StopWatch::time() const
	{
		if (!is_stopped())
		{
			end_ = std::chrono::high_resolution_clock::now();
		}
		return std::chrono::duration_cast<T>(t + std::chrono::duration_cast<std::chrono::nanoseconds>(end_ - start_));
	}
}
