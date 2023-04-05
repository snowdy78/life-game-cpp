#pragma once
namespace rn
{
	struct Button : Rect, ClickableObject
	{
	private:
		class Text : public sf::Text
		{
			const Button *button;
			using sf::Text::setPosition;
			using sf::Text::setOrigin;
			using sf::Text::setScale;
			using sf::Text::setRotation;
			using sf::Text::move;
			using sf::Text::scale;
			using sf::Text::rotate;
		public:
			explicit Text(sf::Text &&text, const Button *button_ref)
				: sf::Text(std::move(text)), button(button_ref)
			{

			}
			Text(const Text &text) = delete;
			
			Text(Text &&text) noexcept = delete;

			Text() = default;
			void setLineSpacing(float spacingFactor);
			void setStyle(sf::Uint32 style);
			void setString(sf::String string);
			void setFont(const sf::Font &font);
			void setCharacterSize(unsigned char_size);
			using sf::Text::getTransform;
			Text &operator=(const Text &text) = delete;
			Text &operator=(Text &&text) noexcept = delete;
			friend struct Button;
		};
	public:
		explicit Button(Vec2f, const sf::String &, const sf::Font &);
		Button(const Button &button);

		Button(Button &&button) noexcept;
		Button() = default;

		void setPosition(const Vec2f &position);
		void setPosition(const float &x, const float &y);
		void setOrigin(const Vec2f &origin);
		void setOrigin(const float &x, const float &y);
		void setScale(const Vec2f &scale);
		void setScale(const float &x, const float &y);
		void setSize(float x, float y);
		void setSize(const Vec2f &sz);
		Vec2f getTextCenterPosition() const;
		bool isIntersected(const Vec2f &p) const override;
		Button::Text content;
		Button &operator=(const Button &button);

		Button &operator=(Button &&button) noexcept;
	private:
		void draw(sf::RenderTarget &window, sf::RenderStates states) const override;
	};

}