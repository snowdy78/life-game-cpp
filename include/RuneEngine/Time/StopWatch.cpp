#include "../Engine.hpp"

namespace rn
{
	StopWatch::StopWatch() = default;

	void StopWatch::onStart()
	{
		if (first_start)
		{
			start_ = std::chrono::high_resolution_clock::now();
			first_start = false;
		}
		end_ = std::chrono::high_resolution_clock::now();
	}

	void StopWatch::onStop()
	{
		end_ = std::chrono::high_resolution_clock::now();
	}

	void StopWatch::reset()
	{
		start_ = std::chrono::high_resolution_clock::now();
		end_ = std::chrono::high_resolution_clock::now();
	}
}
