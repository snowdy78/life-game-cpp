#pragma once


namespace rn
{
	class Table : public sf::Drawable, public sf::Transformable, Matrix<sf::FloatRect>
	{
		Vec2f default_cell_size;
		sf::Color color = sf::Color::White; 
	public:
		Table(const size_t &x, const size_t &y, Vec2f sample);

		Table(const size_t &width, const size_t &height);
		Table() = default;
		class ConstCell
		{
			using ConstRow = rn::Table::ConstRow;
			using ConstIterator = rn::Table::ConstRow::ConstIterator;

			class YIterator
			{
				size_t y;
				explicit YIterator(size_t row) : y(row){}
				
				friend class Table;
				friend class ConstCell;
			public:
				explicit operator size_t() const
				{
					return y;
				}
				YIterator operator+(int d) const
				{
					return YIterator(y + d);
				}
				YIterator operator-(int d) const
				{
					return YIterator(y - d);
				}
				YIterator operator++() // prefix
				{
					YIterator i = *this;
					y += 1;
					return i;
				}
				YIterator &operator++(int) // postfix
				{
					++y;
					return *this;
				}
				YIterator operator--() // prefix
				{
					YIterator i = *this;
					y -= 1;
					return i;
				}
				YIterator &operator--(int) // postfix
				{
					--y;
					return *this;
				}
				YIterator &operator+=(int d)
				{
					y += d;
					return *this;
				}
				YIterator &operator-=(int d)
				{
					y -= d;
					return *this;
				}
				bool operator==(YIterator row) const
				{
					return y == row.y;
				}
				bool operator>=(YIterator row) const
				{
					return y >= row.y;
				}
				bool operator>(YIterator row) const
				{
					return y > row.y;
				}
				bool operator<=(YIterator row) const
				{
					return y <= row.y;
				}
				bool operator<(YIterator row) const
				{
					return y < row.y;
				}
				bool operator!=(YIterator row) const
				{
					return y != row.y;
				}
			};
			class XIterator
			{
				size_t x;
				explicit XIterator(size_t column) : x(column) {}
				friend class Table;
				friend class ConstCell;
			public:
				explicit operator size_t() const
				{
					return x;
				}
				XIterator operator+(int d) const
				{
					return XIterator(x + d);
				}
				XIterator operator-(int d) const
				{
					return XIterator(x - d);
				}
				XIterator operator++() // prefix
				{
					XIterator i = *this;
					x += 1;
					return i;
				}
				XIterator &operator++(int) // postfix
				{
					++x;
					return *this;
				}
				XIterator operator--() // prefix
				{
					XIterator i = *this;
					x -= 1;
					return i;
				}
				XIterator &operator--(int) // postfix
				{
					--x;
					return *this;
				}
				XIterator &operator+=(int d)
				{
					x += d;
					return *this;
				}
				XIterator &operator-=(int d)
				{
					x -= d;
					return *this;
				}
				bool operator==(XIterator column) const
				{
					return x == column.x;
				}
				bool operator>=(XIterator column) const
				{
					return x >= column.x;
				}
				bool operator>(XIterator column) const
				{
					return x > column.x;
				}
				bool operator<=(XIterator column) const
				{
					return x <= column.x;
				}
				bool operator<(XIterator column) const
				{
					return x < column.x;
				}
				bool operator!=(XIterator column) const
				{
					return x != column.x;
				}
			};
			const Table *table = nullptr;
			explicit ConstCell(const Table *table, size_t column = 0, size_t row = 0)
				:
				table(table),
				y(row),
				x(column) {}
			friend class Table;
			ConstCell::ConstIterator get_iterator() const
			{
				return (table->begin_row() + y.y).begin() + x.x;
			}
		public:
			YIterator y;
			XIterator x;

			const sf::FloatRect &operator*() const
			{
				return *get_iterator();
			}
			const sf::FloatRect *operator->() const
			{
				return &*get_iterator();
			}
			bool operator==(ConstCell cell) const
			{
				return this == &cell or x == cell.x and y == cell.y;
			}
			bool operator!=(ConstCell cell) const
			{
				return !(*this == cell);
			}
		};


		using ConstRow = Matrix::ConstRow;
		using ConstColumn = Matrix::ConstColumn;
		using Matrix<sf::FloatRect>::empty;
		ConstCell getCell(const size_t &column, const size_t &row) const;
		ConstCell getCell(ConstRow row, ConstRow::ConstIterator cell) const;
		ConstCell getCell(ConstColumn row, ConstColumn::ConstIterator cell) const;
	
		ConstRow begin_row() const;
		ConstRow cbegin_row() const;
		ConstColumn begin_column() const;
		ConstColumn cbegin_column() const;
		ConstRow end_row() const;
		ConstRow cend_row() const;
		ConstColumn end_column() const;
		ConstColumn cend_column() const;
		ConstRow row(const size_t &) const;
		ConstColumn column(const size_t &) const;
		size_t getColumnCount() const;
		size_t getRowCount() const;
		size_t getCellCount() const;
		void resize(const size_t &width, const size_t &height);
		void setColumnWidth(const size_t &, const float &);
		void setRowHeight(const size_t &, const float &);
		void setCellsSize(const Vec2f &);
		void setBorderColor(sf::Color color);
		Vec2f getSize() const;
		Vec2f getCellPosition(const size_t &x, const size_t &y) const;
		Vec2f getCellSize(const size_t &x, const size_t &y) const;
		sf::FloatRect getColumnRect(const size_t &) const; // returns global bounds of column
		sf::FloatRect getRowRect(const size_t &) const; // returns global bounds of line 
		sf::FloatRect getCellRect(const size_t &, const size_t &) const; // returns global bounds of cell
		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBounds() const;
	private:
		void setCellSize(const size_t &x, const size_t &y, const Vec2f &);
		const sf::FloatRect &at(const size_t &, const size_t &) const;
		sf::FloatRect &at(const size_t &, const size_t &);
		void recount_cells_positions();

		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};

}
