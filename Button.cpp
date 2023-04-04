
#include "LifeGame.hpp"

namespace lg
{
	Button::Button(const Vec2f &size, const std::string &string)
		: rn::Button(size, string, fonts::MultiroundPro)
	{
		content.setFillColor(button_text_color);
		setFillColor(button_color);
	}

	Button::Button(const std::string& str)
		: rn::Button(Vec2f{ 0, 0 }, str, fonts::MultiroundPro)
	{
	}
}
