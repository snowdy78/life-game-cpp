#pragma once


namespace rn
{
	class Table : public sf::Drawable, public sf::Transformable, Matrix<sf::FloatRect>
	{
		Vec2f default_cell_size; 
	public:
		Table(const size_t &x, const size_t &y, Vec2f sample)
			: Matrix<sf::FloatRect>(x, y, sf::FloatRect())
		{
			setCellsSize(sample);
		}
		Table(const size_t &width, const size_t &height)
			: Matrix<sf::FloatRect>(width, height, sf::FloatRect()) {}
		Table() = default;
		using ConstRow = Matrix::ConstRow;
		using ConstColumn = Matrix::ConstColumn;
		using Matrix<sf::FloatRect>::empty;
		auto begin_row() const;
		auto cbegin_row() const;
		auto begin_column() const;
		auto cbegin_column() const;
		auto end_row() const;
		auto cend_row() const;
		auto end_column() const;
		auto cend_column() const;
		auto row(const size_t &) const;
		auto column(const size_t &) const;
		size_t getColumnCount() const { return column_count(); }
		size_t getRowCount() const { return row_count(); }
		size_t getCellCount() const { return row_count()*column_count(); }
		void resize(const size_t &width, const size_t &height);
		void setColumnWidth(const size_t &, const float &);
		void setRowHeight(const size_t &, const float &);
		void setCellsSize(const Vec2f &);
		Vec2f getSize() const;
		Vec2f getCellPosition(const size_t &x, const size_t &y) const;
		Vec2f getCellSize(const size_t &x, const size_t &y) const;
		sf::FloatRect getColumnRect(const size_t &) const; // returns global bounds of column
		sf::FloatRect getRowRect(const size_t &) const; // returns global bounds of line 
		sf::FloatRect getCellRect(const size_t &, const size_t &) const; // returns global bounds of cell
		sf::FloatRect getGlobalBounds() const { return {getPosition(), getSize()}; }
		sf::FloatRect getLocalBounds() const { return {Vec2f(), getSize()}; }
	private:
		void setCellSize(const size_t &x, const size_t &y, const Vec2f &);
		const sf::FloatRect &at(const size_t &, const size_t &) const;
		sf::FloatRect &at(const size_t &, const size_t &);
		void recount_cells_positions();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};

	inline auto Table::begin_row() const
	{ return Matrix::begin_row(); }

	inline auto Table::cbegin_row() const
	{ return Matrix::cbegin_row(); }

	inline auto Table::begin_column() const
	{ return Matrix::begin_column(); }

	inline auto Table::cbegin_column() const
	{ return Matrix::cbegin_column(); }

	inline auto Table::end_row() const
	{ return Matrix::end_row(); }

	inline auto Table::cend_row() const
	{ return Matrix::cend_row(); }

	inline auto Table::end_column() const
	{ return Matrix::end_column(); }

	inline auto Table::cend_column() const
	{ return Matrix::cend_column(); }

	inline auto Table::row(const size_t &y) const
	{
		return Matrix::row(y);
	}
	inline auto Table::column(const size_t &x) const
	{
		return Matrix::column(x);
	}
	inline void Table::setCellSize(const size_t& x, const size_t& y, const Vec2f &size)
	{
		sf::FloatRect &cell = at(x, y);
		cell = sf::FloatRect(cell.left, cell.top, size.x, size.y);
	}
	
	inline Vec2f Table::getCellPosition(const size_t &x, const size_t &y) const
	{
		auto cell = getCellRect(x, y);
		return { cell.left, cell.top };
	}
	inline Vec2f Table::getCellSize(const size_t &x, const size_t &y) const
	{
		auto cell = getCellRect(x, y);
		return { cell.width, cell.height };
	}


	inline void Table::resize(const size_t &width, const size_t &height)
	{
		size_t before_width = getColumnCount();
		size_t before_height = getRowCount();
		Matrix::resize(width, height);
		for (size_t y = before_height; y < getRowCount(); ++y)
		{
			for (size_t x = 0; x < getColumnCount(); ++x)
			{
				at(x, y) = { {0, 0}, default_cell_size };
			}
		}
		for (size_t x = before_width; x < getColumnCount(); ++x)
		{
			for (size_t y = 0; y < before_height; ++y)
			{
				at(x, y) = { {0, 0}, default_cell_size };
			}
		}
		recount_cells_positions();
	}

	inline void Table::setColumnWidth(const size_t &x, const float &width)
	{
		for (size_t y = 0; y < Matrix::row_count(); y++)
			setCellSize(x, y, Vec2f(width, at(x, y).height));
		recount_cells_positions();
	}
	inline void Table::setRowHeight(const size_t &y, const float &height)
	{
		for (size_t x = 0; x < Matrix::column_count(); x++)
			setCellSize(x, y, Vec2f(at(x, y).width, height));
		recount_cells_positions();
	}

	inline const sf::FloatRect &Table::at(const size_t &x, const size_t &y) const
	{
		return Matrix::column(x).at(y);
	}
	inline sf::FloatRect &Table::at(const size_t &x, const size_t &y)
	{
		return Matrix::column(x).at(y);
	}
	inline void Table::setCellsSize(const Vec2f &sample)
	{
		default_cell_size = sample;
		Vec2f position;
		for(auto y = Matrix::begin_column(); y != Matrix::end_column(); y.next())
		{
			for(auto x = y.begin(); x != y.end(); x.next())
			{
				*x = sf::FloatRect(position.x, position.y, sample.x, sample.y);
				position.y += sample.y;
			}
			position.y = 0;
			position.x += sample.x;
		}
	}
	
	inline Vec2f Table::getSize() const
	{
		Vec2f ss; // size
		for (auto y = Matrix::begin_row(); y != Matrix::end_row(); ++y)
		{
			ss.y += y.begin()->height;
		}
		for (auto x = Matrix::begin_column(); x != Matrix::end_column(); ++x)
		{
			ss.x += x.begin()->width;
		}
		return ss;
	}
	inline sf::FloatRect Table::getRowRect(const size_t &y) const
	{
		sf::FloatRect box;
		box.width = getSize().x;
		box.height = Matrix::row(y).begin()->height;
		box.left = getPosition().x + Matrix::row(y).begin()->left;
		box.top = getPosition().y + Matrix::row(y).begin()->top;
		return box;
	}
	inline sf::FloatRect Table::getColumnRect(const size_t &x) const
	{
		sf::FloatRect box;
		box.width = column(x).begin()->width;
		box.height = getSize().y;
		box.left = getPosition().x + Matrix::column(x).begin()->left;
		box.top = getPosition().y + Matrix::column(x).begin()->top;
		return box;
	}
	inline sf::FloatRect Table::getCellRect(const size_t &x, const size_t &y) const
	{
		sf::FloatRect box = at(x, y);
		box.left += getPosition().x;
		box.top += getPosition().y;
		return box;
	}
	inline void Table::recount_cells_positions()
	{
		for (auto column = Matrix::begin_column(); column != Matrix::end_column(); ++column)
		{
			float pos_y = 0.f;
			for (auto &cell : column)
			{
				cell.top = pos_y;
				pos_y += cell.height;
			}
		}
		for (auto line = Matrix::begin_row(); line != Matrix::end_row(); ++line)
		{
			float pos_x = 0.f;
			for (auto &cell : line)
			{
				cell.left = pos_x;
				pos_x += cell.width;
			}
		}
	}
	inline void Table::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (!empty())
		{
			sf::VertexArray borders(sf::Lines, 2);
			for (auto column = Matrix::begin_column(); column != Matrix::end_column(); ++column)
			{
				const bool is_last_column = column == Matrix::end_column() - 1;
				for (auto cell = column.begin(); cell != column.end(); ++cell)
				{
					borders[0].position = Vec2f{cell->left, cell->top};
					borders[1].position = borders[0].position + Vec2f{ cell->width, 0 };
					target.draw(borders, states);
					borders[1].position = borders[0].position + Vec2f{ 0, cell->height };
					target.draw(borders, states);
					if (is_last_column)
					{
						borders[0].position = Vec2f(cell->left + cell->width, cell->top);
						borders[1].position = Vec2f(cell->left + cell->width, cell->top + cell->height);
						target.draw(borders, states);
					}
					if (cell == --column.end())
					{
						borders[0].position = Vec2f(cell->left, cell->top + cell->height);
						borders[1].position = Vec2f(cell->left + cell->width, cell->top + cell->height);
						target.draw(borders, states);
					}
				}
			}
		}

	}

}