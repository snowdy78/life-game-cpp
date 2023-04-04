
#include "LifeGame.hpp"

namespace lg
{
	Options::Parameter::~Parameter() = default;

	void Options::reopen_window()
	{
		window.create({ rn::Settings::getResolution().x, rn::Settings::getResolution().y }, "Life Game", rn::Settings::getWindowMode());
		window.setVerticalSyncEnabled(rn::Settings::getVsync());
		window.setFramerateLimit(rn::Settings::getFramerateLimit());
	}

	void Options::start()
	{
		panels.choosePanel(panels.at(0));
		panels.start();
	}
	void Options::update()
	{
		panels.update();
		window.clear(background_color);
		window.draw(panels);
		window.display();
	}
	

	void Options::onEvent(sf::Event& event)
	{
		Vec2f mpos = Vec2f(rn::mouse_position);
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		if (event.key.code == sf::Keyboard::Key::Escape)
		{
			if (rn::Clickable::isKeydown(event.type))
			{
				next_branch(new MainMenu(window));
			}
		}
		panels.onEvent(event);
	}
}
