#pragma once

#include <vector>
#include <iterator>
#include "Cell.hpp"

namespace lg
{
	class CellField : public sf::Drawable
	{
		int x, y;
		std::vector<Cell> cells;
		bool is_started = false;
		std::vector<Cell *> next_frame_live_cells;
		std::vector<Cell *> next_frame_dead_cells;
		rn::StopWatch stopwatch;
	public:
		using Iterator = std::vector<Cell>::iterator;
		using ConstIterator = std::vector<Cell>::const_iterator;
		CellField(int x, int y)
			: x(x), y(y), cells(static_cast<size_t>(x*y), Cell(this))
		{
			resize_cells();
		}
		sf::Vector2i orientation() const
		{
			return { x, y };
		}
		ConstIterator begin() const
		{
			return cells.begin();
		}
		ConstIterator end() const
		{
			return cells.end();
		}
		ConstIterator cbegin() const
		{
			return cells.cbegin();
		}
		ConstIterator cend() const
		{
			return cells.cend();
		}
		// neighbour is living cell
		int get_neighbour_count(ConstIterator iter)
		{
			int nc = 0; // neighbour count
			size_t p = std::distance(begin(), iter);
			size_t px = p % x;
			size_t py = (p - px)/x;
			// left
			if (px > 0) 
				if ((iter - 1)->isLiving())
					nc++;
			// right
			if (px < static_cast<size_t>(x) - 1) 
				if ((iter + 1)->isLiving())
					nc++;
			
			if (py > 0)
			{
				auto v = iter - x;
				if (v->isLiving())
					nc++;
				size_t vp = std::distance(begin(), v);
				size_t vx = vp % x; 
				if (vx > 0) // left top
					if ((v - 1)->isLiving())
						nc++;
				if (vx < static_cast<size_t>(x) - 1) // right top
					if ((v + 1)->isLiving())
						nc++;
			}
			if (py < static_cast<size_t>(y) - 1)
			{
				auto v = iter + x;
				if (v->isLiving())
					nc++;
				size_t vp = std::distance(begin(), v);
				size_t vx = vp % x;
				if (vx > 0) // left bottom
					if ((v - 1)->isLiving()) 
						nc++;
				if (vx < static_cast<size_t>(x) - 1) // right bottom
					if ((v + 1)->isLiving())
						nc++;
			}
			return nc;
		}
		bool wasStarted() const
		{
			return is_started;
		}
		void start()
		{
			is_started = true;
		}
		void stop()
		{
			is_started = false;
		}
		void aliveCell(ConstIterator cell)
		{
			if (!is_started)
			{
				auto icell = std::find(cells.begin(), cells.end(), *cell);
				icell->alive();
			}
			else throw std::exception("cell can't be alive");
		}
		void slayCell(ConstIterator cell)
		{
			if (!is_started)
			{
				auto icell = std::find(cells.begin(), cells.end(), *cell);
				icell->kill();
			}
			else throw std::exception("cell can't be slain");
		}
		void clear()
		{
			for (auto &cell : cells)
			{
				cell.kill();
			}
		}
		void update()
		{
			if (is_started)
			{
				auto &nflc = next_frame_live_cells;
				auto &nfdc = next_frame_dead_cells;
				stopwatch.start();
				using namespace std::chrono;
				if (stopwatch.time<milliseconds>() >= 500ms)
				{
					stopwatch.reset();
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
					for (auto cell = cells.begin(); cell != cells.end(); cell++)
					{
						//////
						
						auto neighbour_count = get_neighbour_count(cell);
						if (neighbour_count == 3 and !cell->isLiving())
						{
							nflc.push_back(&*cell);
						}
						else if (!(neighbour_count == 2 or neighbour_count == 3) and cell->isLiving())
						{
							nfdc.push_back(&*cell);
						}

						//////
						
					}
				}
				stopwatch.stop();
			}
		}
		void draw(sf::RenderTarget& target, sf::RenderStates states) const override
		{
			for (auto &cell : cells)
			{
				target.draw(cell, states);
			}
		}
		void resize_cells()
		{
			float resx = static_cast<float>(rn::Settings::getResolution().x);
			float resy = static_cast<float>(rn::Settings::getResolution().y);
			float countx = static_cast<float>(x), county = static_cast<float>(y);
			int i = 0, j = 0;

			for (auto &cell : cells)
			{
				float x0 = static_cast<float>(i), y0 = static_cast<float>(j);

				cell.setSize(sf::Vector2f(resx / countx, resy / county));
				cell.setPosition(x0 * cell.getSize().x, y0 * cell.getSize().y);
				i++;
				if (i == x)
				{
					i = 0;
					j++;
				}
			}
		}
	private:
	};
}