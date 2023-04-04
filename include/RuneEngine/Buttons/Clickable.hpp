#pragma once
namespace rn
{
	struct Clickable
	{
		virtual ~Clickable() = 0;
		Clickable() = default;
		Clickable(const Clickable &) = default;
		Clickable(Clickable &&) noexcept = default;
		Clickable &operator=(const Clickable &) = default;
		Clickable &operator=(Clickable &&) noexcept = default;
		//happens when the key is downed.
		static bool isKeydown(sf::Event::EventType eventtype);
		//keyup: happens when the key is released.
		static bool isKeyup(sf::Event::EventType eventtype);
	};

	
	class ClickableObject : protected Clickable
	{
		mutable bool is_pushed = false;
		mutable bool ready_to_click = false;
	public:
		ClickableObject() = default;
		bool isKeyup(sf::Event::EventType eventtype, const Vec2f &where) const;

		bool isKeydown(sf::Event::EventType eventtype, const Vec2f &where) const;

		// returns true, if key is down inside object and key is up inside object
		bool isClicked(sf::Event::EventType eventtype, const Vec2f &where) const;

		// returns true, if key is down inside object and while not key is up
		bool isPushed(sf::Event::EventType eventtype, const Vec2f &where) const;
		virtual bool isIntersected(const Vec2f &p) const = 0;
	};

	
}
