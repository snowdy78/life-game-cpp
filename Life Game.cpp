
#include <iostream>
#include "LifeGame.hpp"
#include <list>
#include <string>

int main()
{
	sf::RenderWindow window({ rn::Settings::getResolution().x, rn::Settings::getResolution().y }, "Life Game", rn::Settings::getWindowMode());
	using rn::Button;
	lg::CellField cell_field(32, 32);
	sf::Font font;
	font.loadFromFile("Fonts/MultiroundPro.otf");
	sf::Vector2f button_size = { 250, 90 };
	Button play(button_size, "Play", font);
	Button clear(button_size, "Clear", font);
	std::vector buttons = { &play, &clear };
	for (auto &button : buttons)
	{
		button->content.setCharacterSize(36);
		button->content.setFillColor({ 0,0,0 });
		button->setOutlineThickness(3);
		button->setOutlineColor(sf::Color::Black);
		button->setFillColor(sf::Color::White);
	}
	clear.setPosition(0, button_size.y);
	while (window.isOpen())
	{
		sf::Event event;
		sf::Vector2f mpos = sf::Vector2f(sf::Mouse::getPosition(window));
		while(window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
			if (event.type == sf::Event::Resized)
			{
				sf::FloatRect varea = sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height);
				window.setView(sf::View(varea));
				cell_field.resize_cells();
				button_size = { 250, 90 };
				for (auto &button : buttons)
				{
					button->setSize(button_size);
				}
				clear.setPosition(0, button_size.y);
			}
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (play.isKeyup(event.type, mpos))
				{
					if (cell_field.wasStarted())
					{
						cell_field.stop();
						play.content.setString("Start");
					}
					else
					{
						cell_field.start();
						play.content.setString("Stop");
					}
					break;
				}
				if (clear.isKeyup(event.type, mpos))
				{
					cell_field.clear();
					break;
				}
			}
			for (auto &cell : cell_field)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Left) and cell.isIntersected(mpos))
					{
						if (cell.isLiving())
						{
							try
							{
								cell_field.slayCell(std::find(cell_field.begin(), cell_field.end(), cell));
							}
							catch (...)
							{
							
							}
						}
						else
						{
							try
							{
								cell_field.aliveCell(std::find(cell_field.begin(), cell_field.end(), cell));
							} catch(...)
							{
							
							}
						}
					}
				}
			}
		}
		window.clear();
		cell_field.update();
		window.draw(cell_field);
		for (auto cell = cell_field.begin(); cell != cell_field.end(); cell++)
		{
			sf::Text text(std::to_string(cell_field.get_neighbour_count(cell)), font);
			if (cell->isLiving())
			{
				text.setFillColor(sf::Color::White);
			}
			else
			{
				text.setFillColor(sf::Color::Black);
			}
			text.setCharacterSize(static_cast<unsigned>(std::floor(button_size.y/3.f)));
			float w = (cell->getGlobalBounds().width - text.getGlobalBounds().width) / 2.f;
			float h = (cell->getGlobalBounds().height - text.getGlobalBounds().height) / 2.f;
			sf::Vector2f p = sf::Vector2f(text.getGlobalBounds().left, text.getGlobalBounds().top) - text.getPosition();
			sf::Vector2f defaultIndent = sf::Vector2f(w, h);
			text.setPosition(cell->getPosition() + defaultIndent - p);
			window.draw(text);
		}
		window.draw(clear);
		window.draw(play);
		window.display();
	}
}
