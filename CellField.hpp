#pragma once

#include <vector>
#include <iterator>

#include "Cell.hpp"
#include "Cell.hpp"
#include "Cell.hpp"

namespace lg
{
	class CellField : public sf::Drawable, public sf::Transformable, public rn::MonoBehaviour
	{
	public:
		using Iterator = std::vector<Cell>::iterator;
		using ConstIterator = std::vector<Cell>::const_iterator;
	private:
		int x, y;
		using ms = std::chrono::milliseconds;
		bool is_started = false;
		std::vector<Cell *> next_frame_live_cells;
		std::vector<Cell *> next_frame_dead_cells;
		rn::StopWatch stopwatch;
		Cell *choosed = nullptr;
		inline static Vec2f default_size = Vec2f{rn::Settings::getResolution()};
		inline static ms default_speed = ms(500);
		ms speed = default_speed;
		Vec2f size = default_size;
		sf::Color live_color = sf::Color::White,
				  death_color= sf::Color::Black;

		std::vector<int> neighbour_values_when_cell_is_alive = {3};
		std::vector<int> neighbour_values_when_cell_is_still_living = {2, 3};

		std::vector<Cell> cells;

		void kill(Cell &cell);
		void alive(Cell &cell);
		void recount_neighbours_around_cell(Iterator cell);
		// neighbour is living cell
		int get_neighbour_count(ConstIterator iter);
		std::vector<Cell *> get_cells_around(ConstIterator cell);
		friend class Cell;
	public:
		CellField(int x, int y);
		Vec2f getSize() const;

		void setRules(const std::initializer_list<int> &neighbour_values_when_cell_is_alive, const std::initializer_list<int> &neighbour_values_when_cell_is_still_living);

		void setSize(const Vec2f &Size);

		void setPosition(const Vec2f &position);

		void setPosition(float x, float y);

		void setOrigin(const Vec2f &origin);

		void setOrigin(float x, float y);

		void setDeathColor(const sf::Color &color);

		void setLiveColor(const sf::Color &color);

		void diplayCellNeighbourCount(bool show);
		bool isCellNeighbourCountDisplays() const;

		ms getSpeed() const;

		void setSpeed(const ms &speed);

		sf::Vector2i orientation() const;

		
		sf::Color getCellsDeathColor() const;

		sf::Color getCellsLiveColor() const;
		ConstIterator begin() const;
		ConstIterator end() const;
		ConstIterator cbegin() const;
		ConstIterator cend() const;


		void onEvent(sf::Event& event) override;


		bool wasStarted() const;

		void play();

		void stop();

		void clear();
		virtual void onStop() {  }
		virtual void onPlay() {  }
		void update() override;

		void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	private:
		void resize_cells();
	};
}