#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "CellField.hpp"

namespace lg
{
	struct CellRect : rn::Button
	{
	public:
		CellRect(bool liveness = false)
			: Button(Vec2f(), std::to_string(liveness), fonts::MultiroundPro)
		{
		}
		bool isIntersected(const Vec2f& p) const override
		{
			auto g = getGlobalBounds();
			return	p.x > g.left and p.x < g.left + g.width and
					p.y > g.top and p.y < g.top + g.height;
		}
	};
	class Cell : public CellRect, public rn::MonoBehaviour
	{
		CellField *field;
		int neighbour_count = 0;
		size_t index = 0; // position on the field
		bool is_living = false;
		using RectangleShape::setFillColor;
		bool is_show = true;
		friend class CellField;
		Cell(CellField &cell_field, bool liveness = false);
		void setNeighbourCount(int count);
		void kill();
		void alive();
	public:
		bool isLiving() const;
		void displayNeighbourCount(bool is_show);
		bool isDisplayNeighbourCount() const
		{
			return is_show;
		}
		int getNeighbourCount() const;
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			target.draw(rn::Rect(*this), states);
			if (is_show)
				target.draw(content, states);
		}
		bool operator==(const Cell &cell) const;

		bool operator!=(const Cell &cell) const;
	};
}
