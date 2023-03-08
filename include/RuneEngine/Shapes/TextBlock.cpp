#include "../Engine.hpp"

namespace rn
{
	TextBlock::TextBlock(const Vec2f &size, const sf::String &string, const sf::Font &font,
		const unsigned &char_size) : Text("", font, char_size), bounds(size)
	{
		put_string(string);
	}

	void TextBlock::setSize(const Vec2f& _size)
	{
		bounds = _size;
		put_string(getString());
	}

	Vec2f TextBlock::getSize() const
	{
		return bounds;
	}

	void TextBlock::setString(const sf::String& string)
	{
		put_string(string);
	}

	void TextBlock::setFont(const sf::Font& font)
	{
		Text::setFont(font);
		put_string(getString());
	}

	void TextBlock::setStyle(const sf::Uint32 style)
	{
		Text::setStyle(style);
		put_string(getString());
	}

	sf::Text TextBlock::getLine(const size_t& id) const
	{
		sf::String string;
		size_t n = 0;
		auto this_string = getString();
		for (size_t x = 0; x < this_string.getSize(); x++)
		{
			auto &character = this_string[x];
			if (n == id)
				string += character;
				
			if (character == '\n')
				n++;
		}
		Text txt = static_cast<Text>(*this);
		txt.setString(string);
		return txt;
	}

	size_t TextBlock::getLineCount() const
	{
		std::string string = getString();
		const size_t n = std::count(string.cbegin(), string.cend(), '\n');
		return n + 1;
	}

	sf::String TextBlock::push_back(Text text, const char& character) const
	{ // allocate non-static memory
		auto string = sf::String(text.getString());
		auto string1 = sf::String{ string + character };
		text.setString(string1);
		if (text.getGlobalBounds().width > bounds.x)
		{
			text.setString(string + "\n" );
			if (text.getGlobalBounds().height > bounds.y)
				throw too_long();
			return string + "\n";
		}
		return string1;
	}

	void TextBlock::put_string(const sf::String& string)
	{
		std::vector<sf::String> lines;
		sf::String incr_string;
		{
			Text txt = static_cast<Text>(*this);
			for (auto &character : string)
			{
				txt.setString(incr_string);
				try
				{
					incr_string = push_back(txt, static_cast<char>(character));
				} catch(too_long &)
				{
					break;
				}
				if (*--incr_string.end() == '\n')
				{
					lines.push_back(incr_string);
					if (character != '\n')
						incr_string = character;
					else incr_string = "";
				}
			}
		}
		lines.push_back(incr_string);
		sf::String full_string;
		Text txt = static_cast<Text>(*this);
		for (auto &line : lines)
		{
			full_string += line;
			txt.setString(full_string);
			if (txt.getGlobalBounds().height < bounds.y)
				Text::setString(full_string);
			else break;
		}
	}

	void TextBlock::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(Text(*this), states);
	}
}
