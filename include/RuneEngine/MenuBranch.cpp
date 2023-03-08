#include "Engine.hpp"
#include "MenuBranch.hpp"

namespace rn
{
	MenuBranch::MenuBranch(sf::RenderWindow &window) : window(window)
	{
	}
	void MenuBranch::action()
	{
		mouse_position = sf::Mouse::getPosition(window);
		start();
		rn::StopWatch stopwatch;
		using namespace std::chrono;
		unsigned frame_count = 0;
		while (window.isOpen() and branch == nullptr)
		{
			stopwatch.start();
			sf::Event event;
			while(window.pollEvent(event))
			{
				onEvent(event);
			}
			update();
			mouse_position = sf::Mouse::getPosition(window);
			stopwatch.stop();
			if (stopwatch.time<seconds>() >= 1s)
			{
				FPS = frame_count;
				frame_count = 0;
				stopwatch.reset();
			}
			frame_count++;
		}
	}

	MenuBranch *MenuBranch::getNextBranch()
	{
		return branch;
	}
	void MenuBranch::next_branch(MenuBranch *branch_)
	{
		branch = branch_;
	}

	void MenuBranch::start_branch(MenuBranch *current_branch)
	{
		while (current_branch->window.isOpen())
		{
			branch = nullptr;
			current_branch->action();
			delete current_branch;
			current_branch = branch;
			if (current_branch == nullptr)
				break;
		}
		delete current_branch;
	}

	MenuBranch::~MenuBranch() = default;
}