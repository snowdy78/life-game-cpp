#pragma once


namespace rn
{
	class Table : public sf::Drawable, public sf::Transformable, Matrix<sf::FloatRect>
	{
		Vec2f default_cell_size; 
	public:
		Table(const size_t &x, const size_t &y, Vec2f sample);

		Table(const size_t &width, const size_t &height);
		Table() = default;
		using ConstRow = Matrix::ConstRow;
		using ConstColumn = Matrix::ConstColumn;
		using Matrix<sf::FloatRect>::empty;
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