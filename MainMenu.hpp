#pragma once


namespace lg
{
	class MainMenu : public rn::MenuBranch
	{
		class Button : public lg::Button
		{
			using lg::Button::setSize;
		public:
			Button(const std::string &value)
				: lg::Button(getSize(), value)
			{
			}
			static Vec2f getSize()
			{
				return { Vec2f(rn::Settings::getResolution()).x / 6.f, Vec2f(rn::Settings::getResolution()).y / 12.f };
			}
		};
		Vec2f res = Vec2f(rn::Settings::getResolution());
		Button start_button = Button{"START"};
		Button settings_button = Button{"SETTINGS"};
		Button exit_button = Button{"EXIT"};
		std::vector<Button *> buttons = {&start_button, &settings_button, &exit_button};
		Vec2f padding = Vec2f(0, res.y/18.f);
		rn::Table align_of_buttons = {1, 3, Button::getSize() + padding};


	public:
		MainMenu(sf::RenderWindow &window)
		: MenuBranch(window) {}

		void start() override;
		void update() override;
		void onEvent(sf::Event& event) override;
	};
}