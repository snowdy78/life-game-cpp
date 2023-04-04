#include "LifeGame.hpp"
#include "StartGame.hpp"
#include <chrono>
namespace lg
{
	void StartGame::start()
	{
		font.loadFromFile("Fonts/MultiroundPro.otf");
		cell_field.play_button = &play;
		for (size_t y = 0; y < vertical_buttons.getRowCount(); y++)
		{
			for (size_t x = 0; x < vertical_buttons.getColumnCount(); x++)
			{
				vbuttons[y]->setPosition(vertical_buttons.getCellPosition(x, y));
			}
		}
		vertical_buttons.setBorderColor(button_text_color);
		cell_field.setDeathColor(button_color);
		cell_field.setLiveColor(button_text_color);
		cell_field.setSize(res - Button::getSize());
		using namespace std::chrono_literals;
		cell_field.setSpeed(100ms);
		cell_field.setRules({ 3 }, { 4, 3 });
		cell_field.setPosition(Button::getSize());
		clear.setPosition(0, clear.getSize().y);
	}
	void StartGame::update()
	{
		window.clear(background_color);
		cell_field.update();
		window.draw(cell_field);
		window.draw(clear);
		window.draw(play);
		window.draw(vertical_buttons);
		window.display();
	}
	void StartGame::onEvent(sf::Event &event)
	{
		Vec2f mpos = Vec2f(rn::mouse_position);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.key.code == sf::Keyboard::Escape)
		{
			if (rn::Clickable::isKeydown(event.type))
			{
				next_branch(new MainMenu(window));
			}
		}
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (play.isClicked(event.type, mpos))
			{
				if (cell_field.wasStarted())
				{
					cell_field.stop();
				}
				else
				{
					cell_field.play();
				}
				return;
			}
			if (clear.isClicked(event.type, mpos))
			{
				cell_field.clear();
				cell_field.stop();
				return;
			}
		}
		cell_field.onEvent(event);
	}
}