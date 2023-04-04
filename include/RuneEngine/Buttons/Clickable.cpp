#include "../Engine.hpp"

namespace rn
{

	Clickable::~Clickable() = default;

	bool Clickable::isKeydown(sf::Event::EventType eventtype)
	{
		return eventtype == sf::Event::MouseButtonPressed or eventtype == sf::Event::KeyPressed;
	}

	bool Clickable::isKeyup(sf::Event::EventType eventtype)
	{
		return eventtype == sf::Event::MouseButtonReleased or eventtype == sf::Event::KeyReleased;
	}



	bool ClickableObject::isKeyup(sf::Event::EventType eventtype, const Vec2f &where) const
	{
		return isIntersected(where) and Clickable::isKeyup(eventtype);
	}

	bool ClickableObject::isKeydown(sf::Event::EventType eventtype, const Vec2f &where) const
	{
		return isIntersected(where) and Clickable::isKeydown(eventtype);
	}

	bool ClickableObject::isClicked(sf::Event::EventType eventtype, const Vec2f &where) const
	{
		if (isKeydown(eventtype, where))
		{
			ready_to_click = true;
		}
		else if (Clickable::isKeyup(eventtype) and ready_to_click)
		{
			ready_to_click = false;
			return isIntersected(where);
		}
		return false;
	}

	bool ClickableObject::isPushed(sf::Event::EventType eventtype, const Vec2f &where) const
	{
		if (isKeydown(eventtype, where))
			is_pushed = true;
		if (Clickable::isKeyup(eventtype))
			is_pushed = false;
		return is_pushed;
	}
}