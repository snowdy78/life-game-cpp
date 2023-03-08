#pragma once

namespace rn
{
	class Watch
	{
		bool stopped = true;
	public:
		virtual ~Watch();

		void start();

		void stop();

		bool is_stopped() const;
		virtual void onStop() = 0;
		virtual void onStart() = 0;
	};

	
}
