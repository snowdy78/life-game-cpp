#pragma once


namespace rn
{
	class TextBlock : public sf::Text
	{
		Vec2f bounds;
	public:
		using Text::getGlobalBounds;
		using Text::getLocalBounds;
		TextBlock(const Vec2f &size, const sf::String &string, const sf::Font &font, const unsigned &char_size = 30);

		void setSize(const Vec2f &_size);

		Vec2f getSize() const;

		void setString(const sf::String &string);

		void setFont(const sf::Font &font);

		void setStyle(const sf::Uint32 style);

		Text getLine(const size_t &id) const;

		size_t getLineCount() const;
	private:
		struct too_long : std::exception
		{
			too_long(const char *string) : exception(string) {}
			too_long() = default;
		};
		sf::String push_back(Text text, const char &character) const;

		void put_string(const sf::String &string);

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};

	
}
