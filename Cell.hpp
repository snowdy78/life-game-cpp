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
		void update_neighbour_count(size_t count);
		friend class CellField;
	public:
		Cell(CellField &cell_field, bool liveness = false);
		bool isLiving() const;

		void setNeighbourCount(int count);

		int getNeighbourCount() const;
		void kill();
		void alive();

		bool operator==(const Cell &cell) const;

		bool operator!=(const Cell &cell) const;
	};
}
