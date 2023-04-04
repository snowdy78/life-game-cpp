#pragma once
#include "CellField.hpp"
namespace lg
{
	class StartGame : public rn::MenuBranch
	{
		class Button : public lg::Button
		{
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
		class CellField : public lg::CellField
		{
			void onStop() override
			{
				if (play_button != nullptr)
				{
					std::cout << "stopping\n";
					play_button->setFillColor(button_color);
					play_button->content.setFillColor(button_text_color);
					play_button->content.setString("Play");
				}
			}
			void onPlay() override
			{
				if (play_button != nullptr)
				{
					std::cout << "starting\n";
					play_button->setFillColor(hold_button_color);
					play_button->content.setFillColor(hold_button_text_color);
					play_button->content.setString("Stop");
				}
			}
		public:
			Button *play_button = nullptr;
			using lg::CellField::CellField;
		};
		
		Vec2f res = Vec2f(rn::Settings::getResolution());
		CellField cell_field = CellField(48, 27);
		sf::Font font;
		Button play = Button("Play");
		Button clear = Button("Clear");
		std::vector<Button *> buttons = { &play, &clear };
		std::vector<Button *> vbuttons = { &play, &clear };
		rn::Table vertical_buttons = { 1, vbuttons.size(), Button::getSize() };
	public:
		StartGame(sf::RenderWindow &window)
			: MenuBranch(window)
		{
			
		}
		void start() override;
		void update() override;
		void onEvent(sf::Event& event) override;
	};
}
