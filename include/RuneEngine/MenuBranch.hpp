#pragma once

namespace rn
{
	class MenuBranch : public MonoBehaviour
	{
		inline static MenuBranch *branch = nullptr;
	protected:
		sf::RenderWindow &window;
	public:
		explicit MenuBranch(sf::RenderWindow &window);
		MenuBranch(MenuBranch &&) noexcept = delete;
		MenuBranch(const MenuBranch &) = delete;
		MenuBranch() = delete;
		~MenuBranch() override = 0;
		static MenuBranch *getNextBranch();
		static void next_branch(MenuBranch *branch);
		static void start_branch(MenuBranch *branch);
		void action();
		MenuBranch &operator=(MenuBranch &&) noexcept = delete;
		MenuBranch &operator=(const MenuBranch &branch) = delete;

	};
}