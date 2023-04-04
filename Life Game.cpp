
#include <iostream>
#include "LifeGame.hpp"
#include <list>
#include <string>

int main()
{
	sf::RenderWindow window({ rn::Settings::getResolution().x, rn::Settings::getResolution().y }, "Life Game", rn::Settings::getWindowMode());
	sf::Image icon;
	if (!icon.loadFromFile("icon.png"))
	{
		std::cout << "[ERROR] Can't load Icon\n";
		throw;
	}
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	rn::MenuBranch::start_branch(new lg::MainMenu(window));
}
