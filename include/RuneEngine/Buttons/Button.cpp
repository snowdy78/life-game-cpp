#include "../Engine.hpp"

namespace rn
{
	void Button::Text::setLineSpacing(float spacingFactor)
	{
		sf::Text::setLineSpacing(spacingFactor);
		setPosition(button->getTextCenterPosition());
	}
	void Button::Text::setStyle(sf::Uint32 style)
	{
		sf::Text::setStyle(style);
		setPosition(button->getTextCenterPosition());
	}

	void Button::Text::setString(sf::String string)
	{
		sf::Text::setString(string);
		setPosition(button->getTextCenterPosition());
	}

	void Button::Text::setFont(const sf::Font &font)
	{
		sf::Text::setFont(font);
		setPosition(button->getTextCenterPosition());
	}

	void Button::Text::setCharacterSize(unsigned char_size)
	{
		sf::Text::setCharacterSize(char_size);
		setPosition(button->getTextCenterPosition());
	}

	Button::Button(const Rect &rect, const sf::String &string, const sf::Font &font)
		: content(sf::Text(string, font), this)
	{
		setSize(rect.getSize());
		content.setPosition(getTextCenterPosition());
	}
	Button::Button(const Vec2f &size, const sf::String &string, const sf::Font &font)
		: content(sf::Text{ string, font }, this)
	{
		setSize(size);
		content.setPosition(getTextCenterPosition());

	}
	void Button::setPosition(const Vec2f &position)
	{
		Rect::setPosition(position);
		content.setPosition(getTextCenterPosition());
	}
	void Button::setOrigin(const Vec2f &origin)
	{
		Rect::setOrigin(origin);
		content.setOrigin(origin);
		content.setPosition(getTextCenterPosition());
	}


	void Button::setScale(const Vec2f &scale)
	{
		Rect::setScale(scale);
		content.setScale(scale);
		content.setPosition(getTextCenterPosition());
	}
	void Button::setString(const sf::String &str)
	{
		content.setString(str);
		content.setPosition(getTextCenterPosition());
	}

	void Button::setIndents(const float &left, const float &top)
	{
		indents = Vec2f(left, top);
		content.setOrigin(indents);
	}

	void Button::setIndents(const Vec2f &indents)
	{
		this->indents = Vec2f(indents);
		content.setOrigin(indents);
	}

	void Button::setSize(const Vec2f &size)
	{
		Rect::setSize(size);
		content.setCharacterSize(static_cast<unsigned>(abs(round(getSize().y / 2.f))));
		content.setPosition(getTextCenterPosition());
	}

	sf::Vector2f Button::getIndents() const
	{
		return indents;
	}

	Vec2f Button::getTextCenterPosition() const
	{
		float w = (getGlobalBounds().width - content.getGlobalBounds().width) / 2.f;
		float h = (getGlobalBounds().height - content.getGlobalBounds().height) / 2.f;
		Vec2f p = Vec2f(content.getGlobalBounds().left, content.getGlobalBounds().top) - content.getPosition();
		Vec2f defaultIndent = Vec2f(w, h);
		return getPosition() - getOrigin() + defaultIndent - p;
	}

	bool Button::isIntersected(const Vec2f& p) const
	{
		return math::contains(Rect(*this), p);
	}

	void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
	{
		window.draw(Rect(*this), states);
		window.draw(content, states);
	}
}