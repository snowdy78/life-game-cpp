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

	Button::Button(Vec2f size, const sf::String &string, const sf::Font &font)
		: content(sf::Text{ string, font }, this)
	{
		setSize(size);
		content.setFillColor(sf::Color::Black);
		content.setPosition(getTextCenterPosition());

	}

	Button::Button(const Button& button): Rect(button), content(sf::Text(button.content), this)
	{
			
	}

	Button::Button(Button&& button) noexcept: Rect(std::move(button)), content(sf::Text(std::move(button.content)), this)
	{
			
	}

	void Button::setPosition(const Vec2f &position)
	{
		Rect::setPosition(position);
		content.setPosition(getTextCenterPosition());
	}

	void Button::setPosition(const float& x, const float& y)
	{
		setPosition(Vec2f(x, y));
	}

	void Button::setOrigin(const Vec2f &origin)
	{
		Rect::setOrigin(origin);
		content.setOrigin(origin);
		content.setPosition(getTextCenterPosition());
	}

	void Button::setOrigin(const float& x, const float& y)
	{
		setOrigin(Vec2f(x, y));
		content.setPosition(getTextCenterPosition());
	}


	void Button::setScale(const Vec2f &scale)
	{
		Rect::setScale(scale);
		content.setScale(scale);
		content.setPosition(getTextCenterPosition());
	}

	void Button::setScale(const float& x, const float& y)
	{
		setScale(Vec2f(x, y));
	}

	
	void Button::setSize(float x, float y)
	{
		Button::setSize(Vec2f(x, y));
	}

	void Button::setSize(const Vec2f &size)
	{
		Rect::setSize(size);
		content.setCharacterSize(static_cast<unsigned>(abs(std::round(getSize().y / 2.f))));
		content.setPosition(getTextCenterPosition());
	}

	Vec2f Button::getTextCenterPosition() const
	{
		sf::FloatRect cgb = content.getGlobalBounds();
		sf::FloatRect gb = getGlobalBounds();
		float w = (gb.width - cgb.width) / 2.f;
		float h = (gb.height - cgb.height) / 2.f;
		Vec2f p = Vec2f(cgb.left, cgb.top) - content.getPosition();
		Vec2f defaultIndent = Vec2f(w, h);
		return getPosition() - getOrigin() + defaultIndent - p;
	}

	bool Button::isIntersected(const Vec2f& p) const
	{
		return math::contains(getGlobalBounds(), p);
	}

	Button& Button::operator=(const Button& button)
	{
		if (this != &button)
		{
			static_cast<Rect &>(*this) = static_cast<const Rect &>(button);
			static_cast<sf::Text &>(content) = static_cast<const sf::Text &>(button.content);
			content.button = this;
		}
		return *this;
	}

	Button& Button::operator=(Button&& button) noexcept
	{
		if (this != &button)
		{
			static_cast<Rect &>(*this) = static_cast<const Rect &>(button);
			static_cast<sf::Text &>(content) = static_cast<const sf::Text &>(button.content);
			content.button = this;
		}
		return *this;
	}

	void Button::draw(sf::RenderTarget &window, sf::RenderStates states) const
	{
		window.draw(Rect(*this), states);
		window.draw(content, states);
	}
}