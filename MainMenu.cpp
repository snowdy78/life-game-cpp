#include "LifeGame.hpp"


namespace lg
{
	void MainMenu::start()
	{
		Vec2f res = Vec2f(rn::Settings::getResolution());
		float btn_align_x = (res - align_of_buttons.getSize()).x / 2.f;
		align_of_buttons.setPosition(btn_align_x, res.y - align_of_buttons.getSize().y - padding.y);
		for (size_t y = 0; y < align_of_buttons.getRowCount(); y++)
		{
			buttons[y]->setPosition(align_of_buttons.getCellPosition(0, y));
		}
	}

	void MainMenu::update()
	{
		window.clear(background_color);
		for (auto &button : buttons)
		{
			window.draw(*button);
		}
		
		window.display();
	}

	void MainMenu::onEvent(sf::Event& event)
	{
		if (event.type == sf::Event::Closed)
			window.close();
		Vec2f mpos = Vec2f{rn::mouse_position};
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (start_button.isKeyup(event.type, mpos))
			{
				next_branch(new StartGame(window));
			}
			else if (settings_button.isKeyup(event.type, mpos))
			{
				next_branch(new Options(window));
			}
			else if (exit_button.isKeyup(event.type, mpos))
			{
				window.close();
			}
		}
	}
}
