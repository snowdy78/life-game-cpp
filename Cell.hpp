#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
namespace lg
{
	class Cell : public sf::RectangleShape, public rn::ClickableObject
	{
		CellField *field;
		bool is_living = false;
	public:
		Cell(CellField *cell_field, bool liveness = false)
			: field(cell_field), is_living(liveness)
		{
			setOutlineColor(sf::Color::Black);
			setOutlineThickness(1);
			setFillColor(sf::Color::White);
		}
		bool isLiving() const
		{
			return is_living;
		}
		void kill()
		{
			setFillColor(sf::Color::White);
			is_living = false;
		}
		void alive()
		{
			setFillColor(sf::Color::Black);
			is_living = true;
		}
		bool isIntersected(const sf::Vector2f& p) const override
		{
			return rn::math::contains(*this, p);
		}
		bool operator==(const Cell &cell) const
		{
			return this == &cell;
		}
		bool operator!=(const Cell &cell) const
		{
			return this != &cell;
		}
	};
}
