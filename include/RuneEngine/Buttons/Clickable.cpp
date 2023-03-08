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

	bool ClickableObject::isPushed(sf::Event::EventType eventtype, const Vec2f &where) const
	{
		auto &v = is_pushed;
		if (isKeydown(eventtype, where))
			v = true;
		if (Clickable::isKeyup(eventtype))
			v = false;
		return v;
	}
}