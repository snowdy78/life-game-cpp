#pragma once
namespace rn
{
	struct Button : Rect, ClickableObject
	{
	private:
		class Text : sf::Text
		{
			const Button *button;
		public:
			explicit Text(sf::Text &&text, const Button *button_ref)
				: sf::Text(std::move(text)), button(button_ref)
			{
									
			}
			Text() = default;
			using sf::Text::getPosition;
			using sf::Text::getOrigin;
			using sf::Text::getScale;
			using sf::Text::getRotation;
			using sf::Text::getGlobalBounds;
			using sf::Text::getLocalBounds;
			using sf::Text::setFillColor;
			using sf::Text::getFillColor;
			using sf::Text::findCharacterPos;
			using sf::Text::getCharacterSize;
			using sf::Text::getLetterSpacing;
			using sf::Text::getString;
			using sf::Text::setOutlineColor;
			using sf::Text::getOutlineColor;
			using sf::Text::setOutlineThickness;
			using sf::Text::getOutlineThickness;
			using sf::Text::setColor;
			using sf::Text::getColor;
			void setLineSpacing(float spacingFactor);
			void setStyle(sf::Uint32 style);
			void setString(sf::String string);
			void setFont(const sf::Font &font);
			void setCharacterSize(unsigned char_size);
			using sf::Text::getTransform;
			friend struct Button;
		};
	public:
		explicit Button(const Rect &, const sf::String &, const sf::Font &);
		explicit Button(const Vec2f &, const sf::String &, const sf::Font &);
		Button() = default;
		
		void setPosition(const Vec2f &position);
		void setPosition(const float &x, const float &y) { setPosition(Vec2f(x, y)); }
		void setOrigin(const Vec2f &origin);
		void setOrigin(const float &x, const float &y) { setOrigin(Vec2f(x, y)); }
		void setScale(const Vec2f &scale);
		void setScale(const float &x, const float &y) { setScale(Vec2f(x, y)); }
		void setIndents(const float &, const float &); // top, left, down, right 
		void setIndents(const Vec2f &);
		void setSize(const Vec2f &sz);
		void setString(const sf::String &);
		Vec2f getIndents() const; // left, top
		Vec2f getTextCenterPosition() const;
		bool isIntersected(const Vec2f& p) const override;
		Button::Text content;
	private:
		
		Vec2f indents = Vec2f();
		void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
	};
	
}