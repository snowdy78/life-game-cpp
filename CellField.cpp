#include "LifeGame.hpp"

namespace lg
{
	CellField::CellField(int x, int y)
		: x(x), y(y), cells(static_cast<size_t>(x * y), Cell(*this))
	{
		for (size_t i = 0; i < cells.size(); i++)
		{
			cells[i].index = i;
		}
		resize_cells();
	}

	Vec2f CellField::getSize() const
	{
		return size;
	}

	void CellField::setRules(const std::initializer_list<int> &neighbour_values_when_cell_is_alive, const std::initializer_list<int> &neighbour_values_when_cell_is_still_living)
	{
		if (!is_started)
		{
			this->neighbour_values_when_cell_is_alive.assign(neighbour_values_when_cell_is_alive);
			this->neighbour_values_when_cell_is_still_living.assign(neighbour_values_when_cell_is_still_living);
		}
	}

	void CellField::setSize(const Vec2f& Size)
	{
		size = Size;
		resize_cells();
	}

	void CellField::setPosition(const Vec2f& position)
	{
		Transformable::setPosition(position);
		resize_cells();
	}

	void CellField::setPosition(float x, float y)
	{
		Transformable::setPosition(x, y);
		resize_cells();
	}

	void CellField::setOrigin(const Vec2f& origin)
	{
		Transformable::setOrigin(origin);
		resize_cells();
	}

	void CellField::setOrigin(float x, float y)
	{
		Transformable::setOrigin(x, y);
		resize_cells();
	}

	void CellField::setDeathColor(const sf::Color& color)
	{
		death_color = color;
		for (auto &cell : cells)
		{
			if (!cell.isLiving())
			{
				kill(cell);
			}
			else alive(cell);
		}
	}

	void CellField::setLiveColor(const sf::Color& color)
	{
		live_color = color;
		for (auto &cell : cells)
		{
			if (cell.isLiving())
			{
				alive(cell);
			}
			else kill(cell);
		}
	}

	void CellField::diplayCellNeighbourCount(bool show)
	{
		for (auto &cell : cells)
		{
			cell.displayNeighbourCount(show);
		}
	}

	bool CellField::isCellNeighbourCountDisplays() const
	{
		return begin()->isDisplayNeighbourCount();
	}

	CellField::ms CellField::getSpeed() const
	{
		return speed;
	}

	void CellField::setSpeed(const ms& speed)
	{
		this->speed = speed;
	}

	sf::Vector2i CellField::orientation() const
	{
		return { x, y };
	}
	
	sf::Color CellField::getCellsDeathColor() const
	{
		return death_color;
	}

	sf::Color CellField::getCellsLiveColor() const
	{
		return live_color;
	}

	void CellField::kill(Cell &cell) 
	{
		cell.setFillColor(death_color);
		cell.content.setFillColor(live_color);
	}

	void CellField::alive(Cell &cell)
	{
		cell.setFillColor(live_color);
		cell.content.setFillColor(death_color);
	}

	void CellField::recount_neighbours_around_cell(Iterator cell)
	{
		auto cells_around = get_cells_around(cell);
		for (auto &i : cells_around)
		{
			auto iter = cells.begin() + static_cast<long long>(i->index);
			i->setNeighbourCount(get_neighbour_count(iter));
		}
	}

	CellField::ConstIterator CellField::begin() const
	{
		return cells.begin();
	}

	CellField::ConstIterator CellField::end() const
	{
		return cells.end();
	}

	CellField::ConstIterator CellField::cbegin() const
	{
		return cells.cbegin();
	}

	CellField::ConstIterator CellField::cend() const
	{
		return cells.cend();
	}



	void CellField::onEvent(sf::Event &event)
	{
		auto mpos = Vec2f(rn::mouse_position);
		
		if (!is_started)
		{
			rn::StopWatch t;
			for (auto& cell : cells)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (cell.isKeydown(event.type, mpos))
					{
						choosed = &cell;
						if (cell.isLiving())
						{
							cell.kill();
							return;
						}
						cell.alive();
					}
					else if (rn::Clickable::isKeyup(event.type))
					{
						choosed = nullptr;
					}
				}
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (choosed != nullptr)
					{
						if (cell.isLiving() != choosed->isLiving() and cell.isIntersected(mpos))
						{
							if (choosed->isLiving())
							{
								cell.alive();
								return;
							}
							cell.kill();
							break;
						}
					}
					
				}
			}
		
		} 
	}

	int CellField::get_neighbour_count(ConstIterator iter) 
	{
		int nc = 0;
		for (auto &i : get_cells_around(iter))
		{
			if (i->isLiving())
				nc++;
		}
		return nc;
	}

	std::vector<Cell *> CellField::get_cells_around(ConstIterator const_cell)
	{
		std::vector<Cell *> cells;
		auto cell = this->cells.begin() + static_cast<int>(const_cell->index);
		size_t p = cell->index;
		size_t px = p % x;
		size_t py = (p - px) / x;
		auto addLeftRightNeighbours = [this, &cells](size_t p, Iterator i)
		{
			if (p > 0)
				cells.push_back(&*(i - 1));

			if (p < static_cast<size_t>(x) - 1)
				cells.push_back(&*(i + 1));
		};
		// right & left
		addLeftRightNeighbours(px, cell);
		if (py > 0)
		{
			auto v = cell - x;
			cells.push_back(&*v);
			addLeftRightNeighbours(v->index % x, v);
		}
		if (py < static_cast<size_t>(y) - 1)
		{
			auto v = cell + x;
			cells.push_back(&*v);
			addLeftRightNeighbours(v->index % x, v);
		}
		return cells;
	}

	bool CellField::wasStarted() const
	{
		return is_started;
	}

	void CellField::play()
	{
		if (std::any_of(cells.begin(), cells.end(), [](const Cell &cell) { return cell.isLiving(); }))
		{
			is_started = true;
			onPlay();
		}
	}

	void CellField::stop()
	{
		is_started = false;
		onStop();
	}

	void CellField::clear()
	{
		for (auto &cell : cells)
		{
			cell.kill();
		}
		next_frame_live_cells.clear();
		next_frame_dead_cells.clear();
	}

	void CellField::update()
	{
		if (is_started)
		{
			auto &nflc = next_frame_live_cells;
			auto &nfdc = next_frame_dead_cells;
			stopwatch.start();
			if (stopwatch.time<ms>() >= speed)
			{
				for (auto &i : nflc)
				{
					i->alive();
				}
				nflc.clear();
				for (auto &i : nfdc)
				{
					i->kill();
				}
				nfdc.clear();

				// updating field

				for (auto cell = cells.begin(); cell != cells.end(); cell++)
				{
					//////
					using rn::algorithm::in;
					int neighbour_count = cell->getNeighbourCount();
					if (in(neighbour_count, neighbour_values_when_cell_is_alive) and !cell->isLiving())
					{
						nflc.push_back(&*cell);
					}
					else if (cell->isLiving() and !in(neighbour_count, neighbour_values_when_cell_is_still_living))
					{
						nfdc.push_back(&*cell);
					}

					//////
				}

				////////////////
				stopwatch.reset();
				if (next_frame_live_cells.empty())
				{
					stop();
				}
			}
			stopwatch.stop();
		}
	}

	void CellField::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto &cell : cells)
		{
			target.draw(cell, states);
		}
	}
	void CellField::resize_cells()
	{
		float resx = getSize().x;
		float resy = getSize().y;
		float countx = static_cast<float>(x), county = static_cast<float>(y);
		int i = 0, j = 0;

		for (auto &cell : cells)
		{
			float x0 = static_cast<float>(i), y0 = static_cast<float>(j);

			cell.setSize(sf::Vector2f(resx / countx, resy / county));
			cell.setPosition(getPosition() - getOrigin() + Vec2f{x0 * cell.getSize().x, y0 * cell.getSize().y});
			i++;
			if (i == x)
			{
				i = 0;
				j++;
			}
		}
	}
}
