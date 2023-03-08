#include "../Engine.hpp"

namespace rn
{
	Table::Table(const size_t &x, const size_t &y, Vec2f sample) : Matrix<sf::FloatRect>(x, y, sf::FloatRect())
	{
		setCellsSize(sample);
	}

	Table::Table(const size_t& width, const size_t& height): Matrix<sf::FloatRect>(width, height, sf::FloatRect())
	{}

	Table::ConstRow Table::begin_row() const
	{
		return Matrix::begin_row();
	}

	Table::ConstRow Table::cbegin_row() const
	{
		return Matrix::cbegin_row();
	}

	Table::ConstColumn Table::begin_column() const
	{
		return Matrix::begin_column();
	}

	Table::ConstColumn Table::cbegin_column() const
	{
		return Matrix::cbegin_column();
	}

	Table::ConstRow Table::end_row() const
	{
		return Matrix::end_row();
	}

	Table::ConstRow Table::cend_row() const
	{
		return Matrix::cend_row();
	}

	Table::ConstColumn Table::end_column() const
	{
		return Matrix::end_column();
	}

	Table::ConstColumn Table::cend_column() const
	{
		return Matrix::cend_column();
	}

	Table::ConstRow Table::row(const size_t &y) const
	{
		return Matrix::row(y);
	}
	Table::ConstColumn Table::column(const size_t &x) const
	{
		return Matrix::column(x);
	}

	size_t Table::getColumnCount() const
	{
		return column_count();
	}

	size_t Table::getRowCount() const
	{
		return row_count();
	}

	size_t Table::getCellCount() const
	{
		return row_count()*column_count();
	}

	void Table::setCellSize(const size_t &x, const size_t &y, const Vec2f &size)
	{
		sf::FloatRect &cell = at(x, y);
		cell = sf::FloatRect(cell.left, cell.top, size.x, size.y);
	}

	Vec2f Table::getCellPosition(const size_t &x, const size_t &y) const
	{
		auto cell = getCellRect(x, y);
		return { cell.left, cell.top };
	}
	Vec2f Table::getCellSize(const size_t &x, const size_t &y) const
	{
		auto cell = getCellRect(x, y);
		return { cell.width, cell.height };
	}


	void Table::resize(const size_t &width, const size_t &height)
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

	void Table::setColumnWidth(const size_t &x, const float &width)
	{
		for (size_t y = 0; y < Matrix::row_count(); y++)
			setCellSize(x, y, Vec2f(width, at(x, y).height));
		recount_cells_positions();
	}
	void Table::setRowHeight(const size_t &y, const float &height)
	{
		for (size_t x = 0; x < Matrix::column_count(); x++)
			setCellSize(x, y, Vec2f(at(x, y).width, height));
		recount_cells_positions();
	}

	const sf::FloatRect &Table::at(const size_t &x, const size_t &y) const
	{
		return Matrix::column(x).at(y);
	}
	sf::FloatRect &Table::at(const size_t &x, const size_t &y)
	{
		return Matrix::column(x).at(y);
	}
	void Table::setCellsSize(const Vec2f &sample)
	{
		default_cell_size = sample;
		Vec2f position;
		for (auto y = Matrix::begin_column(); y != Matrix::end_column(); y.next())
		{
			for (auto x = y.begin(); x != y.end(); x.next())
			{
				*x = sf::FloatRect(position.x, position.y, sample.x, sample.y);
				position.y += sample.y;
			}
			position.y = 0;
			position.x += sample.x;
		}
	}

	Vec2f Table::getSize() const
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
	sf::FloatRect Table::getRowRect(const size_t &y) const
	{
		sf::FloatRect box;
		box.width = getSize().x;
		box.height = Matrix::row(y).begin()->height;
		box.left = getPosition().x + Matrix::row(y).begin()->left;
		box.top = getPosition().y + Matrix::row(y).begin()->top;
		return box;
	}
	sf::FloatRect Table::getColumnRect(const size_t &x) const
	{
		sf::FloatRect box;
		box.width = column(x).begin()->width;
		box.height = getSize().y;
		box.left = getPosition().x + Matrix::column(x).begin()->left;
		box.top = getPosition().y + Matrix::column(x).begin()->top;
		return box;
	}
	sf::FloatRect Table::getCellRect(const size_t &x, const size_t &y) const
	{
		sf::FloatRect box = at(x, y);
		box.left += getPosition().x;
		box.top += getPosition().y;
		return box;
	}

	sf::FloatRect Table::getGlobalBounds() const
	{
		return {getPosition(), getSize()};
	}

	sf::FloatRect Table::getLocalBounds() const
	{
		return {Vec2f(), getSize()};
	}

	void Table::recount_cells_positions()
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
	void Table::draw(sf::RenderTarget &target, sf::RenderStates states) const
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
					borders[0].position = Vec2f{ cell->left, cell->top };
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