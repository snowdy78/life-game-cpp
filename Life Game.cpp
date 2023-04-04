
#include <iostream>
#include "LifeGame.hpp"
#include <list>
#include <string>

int main()
{
	sf::RenderWindow window({ rn::Settings::getResolution().x, rn::Settings::getResolution().y }, "Life Game", rn::Settings::getWindowMode());
	rn::MenuBranch::start_branch(new lg::MainMenu(window));
}
