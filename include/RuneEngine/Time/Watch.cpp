#include "../Engine.hpp"

namespace rn
{
	Watch::~Watch() = default;

	void Watch::start()
	{
		stopped = false;
		onStart();
	}

	void Watch::stop()
	{
		stopped = true;
		onStop();
	}

	bool Watch::is_stopped() const
	{
		return stopped;
	}
}
