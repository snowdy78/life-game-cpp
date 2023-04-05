#include "LifeGame.hpp"

namespace lg
{

	Cell::Cell(CellField &cell_field, bool liveness)
		: field(&cell_field)
	{
		setOutlineColor(sf::Color::Black);
		setOutlineThickness(1);
		setNeighbourCount(neighbour_count);
		is_living = liveness;
		if (is_living)
			field->alive(*this);
		else field->kill(*this);
	}

	bool Cell::isLiving() const
	{
		return is_living;
	}

	void Cell::displayNeighbourCount(bool is_show)
	{
		this->is_show = is_show;
	}

	void Cell::setNeighbourCount(int count)
	{
		neighbour_count = count;
		content.setString(std::to_string(neighbour_count));
	}

	int Cell::getNeighbourCount() const
	{
		return neighbour_count;
	}

	void Cell::kill() 
	{
		if (is_living == true)
		{
			field->kill(*this);
			is_living = false;
			auto icell = field->cells.begin() + static_cast<long long>(index);
			auto cells_around = field->get_cells_around(icell);
			for (auto &i : cells_around)
			{
				i->setNeighbourCount(i->getNeighbourCount() - 1);
			}
		}
	}

	void Cell::alive()
	{
		if (is_living == false)
		{
			field->alive(*this);
			is_living = true;
			auto icell = field->cells.begin() + static_cast<long long>(index);
			auto cells_around = field->get_cells_around(icell);
			for (auto &i : cells_around)
			{
				i->setNeighbourCount(i->getNeighbourCount() + 1);
			}
		}
	}
	bool Cell::operator==(const Cell& cell) const
	{
		return this == &cell;
	}

	bool Cell::operator!=(const Cell& cell) const
	{
		return this != &cell;
	}
}
