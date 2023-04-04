#pragma once

#include "RuneEngine/Engine.hpp"

namespace lg
{
	using rn::Vec2f;
	using rn::Vec2u;
	using rn::Vec2;
	using rn::Vec2i;

	class Cell;
	class CellField;
	class MainMenu;
	class StartGame;
	class GameSettings;
	class Button;
	inline const sf::Color button_color = { 175, 211, 225 };
	inline const sf::Color button_text_color = { 33, 69, 88 };
	inline const sf::Color hold_button_color = {99, 166, 192};
	inline const sf::Color hold_button_text_color = {0, 45, 73};
	inline const sf::Color unclickable_button_color = { 139, 154, 160 };
	inline const sf::Color unclickable_button_text_color = {190, 211, 219};
	inline const sf::Color background_color = { 38, 34, 73 };
	namespace fonts
	{
		inline sf::Font load_font(const std::string &font_file_path)
		{
			using namespace std::string_literals;
			sf::Font font;
			if (!font.loadFromFile(font_file_path))
			{
				std::cout << "FileNotFoundError: '"s + font_file_path + "' path or file type is not correct";
				throw;
			}
			return font;
		}
		inline sf::Font MultiroundPro = load_font(R"(Fonts\MultiroundPro.otf)");
	}
}

#include "Button.hpp"
#include "Cell.hpp"
#include "CellField.hpp"
#include "StartGame.hpp"
#include "Options.hpp"
#include "MainMenu.hpp"