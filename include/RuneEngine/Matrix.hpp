#pragma once
#include <exception>
#include <stdexcept>
namespace rn
{
	template<class T>
	class Matrix
	{
	private:
		using pointer = T *;
		using reference = T &;
		using const_pointer = const T *;
		using const_reference = T const &;
		std::vector<std::vector<pointer>> lines_;
		std::vector<std::vector<pointer>> columns_;
	public:
		class Row;
		class ConstRow
		{
			typename std::vector<std::vector<pointer>>::const_iterator line;
			explicit ConstRow(typename std::vector<std::vector<pointer>>::const_iterator iter)
				: line(iter) {}
			friend class Matrix<T>;
		public:
			class ConstIterator
			{
				typename std::vector<pointer>::const_iterator const_iterator;
				explicit ConstIterator(typename std::vector<pointer>::const_iterator iter)
					: const_iterator(iter) {}
				friend class Row;
				friend class ConstRow;
				friend class Row::Iterator;
			public:
				ConstIterator &next()
				{
					return ++(*this);
				}
				ConstIterator &back()
				{
					return --(*this);
				}
				ConstIterator &operator++() // prefix
				{
					++const_iterator;
					return *this;
				}
				ConstIterator operator++(int) // postfix
				{
					return ConstIterator(const_iterator++);
				}
				ConstIterator &operator--() // prefix
				{
					--const_iterator;
					return *this;
				}
				ConstIterator operator--(int) // postfix
				{
					return ConstIterator(const_iterator--);
				}
				ConstIterator operator+(long long d) const
				{
					return ConstIterator(const_iterator + d);
				}
				ConstIterator operator-(long long d) const
				{
					return ConstIterator(const_iterator - d);
				}
				ConstIterator &operator+=(long long d)
				{
					const_iterator += d;
					return *this;
				}
				ConstIterator &operator-=(long long d)
				{
					const_iterator -= d;
					return *this;
				}
				bool operator==(const ConstIterator &i) const
				{
					return const_iterator == i.const_iterator;
				}
				bool operator!=(const ConstIterator &i) const
				{
					return const_iterator != i.const_iterator;
				}
				bool operator>(const ConstIterator &i) const
				{
					return const_iterator > i.const_iterator;
				}
				bool operator>=(const ConstIterator &i) const
				{
					return const_iterator >= i.const_iterator;
				}
				bool operator<(const ConstIterator &i) const
				{
					return const_iterator < i.const_iterator;
				}
				bool operator<=(const ConstIterator &i) const
				{
					return const_iterator <= i.const_iterator;
				}

				const_reference operator*() const
				{
					return **const_iterator;
				}

				const_pointer operator->() const
				{
					return *const_iterator;
				}
			};
			ConstRow() = default;
			size_t size() const
			{
				return line->size();
			}
			const_reference at(size_t id) const
			{
				return *line->at(id);
			}
			const_reference operator[](size_t id) const
			{
				return *(*line)[id];
			}
			ConstIterator begin() const
			{
				return ConstIterator(line->begin());
			}
			ConstIterator end() const
			{
				return ConstIterator(line->end());
			}
			ConstIterator cbegin() const
			{
				return ConstIterator(line->begin());
			}
			ConstIterator cend() const
			{
				return ConstIterator(line->end());
			}
			ConstRow &next()
			{
				return ++(*this);
			}
			ConstRow &back()
			{
				return --(*this);
			}
			bool empty() const
			{
				return line->empty();
			}
			ConstRow &operator++() noexcept // prefix
			{
				++line;
				return *this;
			}
			ConstRow operator++(int) noexcept // postfix
			{
				return ConstRow(line++);
			}
			ConstRow &operator--() noexcept // prefix
			{
				--line;
				return *this;
			}
			ConstRow operator--(int) noexcept // postfix
			{
				return ConstRow(line--);
			}
			ConstRow operator+(const typename std::vector<std::vector<T>>::iterator::difference_type &d) const noexcept
			{
				return ConstRow(line + d);
			}
			ConstRow operator-(const typename std::vector<std::vector<T>>::iterator::difference_type &d) const noexcept
			{
				return ConstRow(line - d);
			}
			ConstRow &operator+=(const typename std::vector<std::vector<T>>::iterator::difference_type &d) noexcept
			{
				line += d;
				return *this;
			}
			ConstRow &operator-=(const typename std::vector<std::vector<T>>::iterator::difference_type &d) noexcept
			{
				line -= d;
				return *this;
			}
			bool operator==(const ConstRow &l) const
			{
				return line == l.line;
			}
			bool operator!=(const ConstRow &l) const
			{
				return !(line == l.line);
			}
			bool operator>(const ConstRow &l) const
			{
				return line > l.line;
			}
			bool operator<(const ConstRow &l) const
			{
				return line == l.line;
			}
			bool operator>=(const ConstRow &l) const
			{
				return line > l.line or line == l.line;
			}
			bool operator<=(const ConstRow &l) const
			{
				return line < l.line or line == l.line;
			}
		};
		class Row
		{
			typename std::vector<std::vector<pointer>>::iterator line;
			explicit Row(const typename std::vector<std::vector<pointer>>::iterator &iter)
				: line(iter) {}

			friend class Matrix<T>;
			friend class ConstRow;
		public:
			class Iterator
			{
				typename std::vector<pointer>::iterator iterator;
				explicit Iterator(typename std::vector<pointer>::iterator iter)
					: iterator(iter) {}
				friend class Row;
			public:
				operator typename ConstRow::ConstIterator() const
				{
					return typename ConstRow::ConstIterator(iterator);
				}
				Iterator &next()
				{
					return ++(*this);
				}
				Iterator &back()
				{
					return --(*this);
				}
				Iterator &operator++() // prefix
				{
					++iterator;
					return *this;
				}
				Iterator operator++(int) // postfix
				{
					return Iterator(iterator++);
				}
				Iterator &operator--() // prefix
				{
					--iterator;
					return *this;
				}
				Iterator operator--(int) // postfix
				{
					return Iterator(iterator--);
				}
				Iterator operator+(long long d) const
				{
					return Iterator(iterator + d);
				}
				Iterator operator-(long long d) const
				{
					return Iterator(iterator - d);
				}
				Iterator &operator+=(long long d)
				{
					iterator += d;
					return *this;
				}
				Iterator &operator-=(long long d)
				{
					iterator -= d;
					return *this;
				}
				bool operator==(const typename ConstRow::ConstIterator &i) const
				{
					return iterator == i.const_iterator;
				}
				bool operator!=(const typename ConstRow::ConstIterator &i) const
				{
					return iterator != i.const_iterator;
				}
				bool operator>(const typename ConstRow::ConstIterator &i) const
				{
					return iterator > i.const_iterator;
				}
				bool operator>=(const typename ConstRow::ConstIterator &i) const
				{
					return iterator >= i.const_iterator;
				}
				bool operator<(const typename ConstRow::ConstIterator &i) const
				{
					return iterator < i.const_iterator;
				}
				bool operator<=(const typename ConstRow::ConstIterator &i) const
				{
					return iterator <= i.const_iterator;
				}

				reference operator*()
				{
					return **iterator;
				}
				pointer operator->()
				{
					return *iterator;
				}
				const_reference operator*() const
				{
					return **iterator;
				}
				const_pointer operator->() const
				{
					return *iterator;
				}
			};

			Row() = default;
			size_t size() const
			{
				return line->size();
			}
			reference at(size_t id)
			{
				return *line->at(id);
			}
			reference operator[](size_t id)
			{
				return *(*line)[id];
			}
			const_reference at(size_t id) const
			{
				return *line->at(id);
			}
			const_reference operator[](size_t id) const
			{
				return *(*line)[id];
			}
			bool empty() const
			{
				return line->empty();
			}
			operator ConstRow() const
			{
				return ConstRow(line);
			}
			typename ConstRow::ConstIterator begin() const
			{
				return ConstRow::ConstIterator(line->begin());
			}
			typename ConstRow::ConstIterator end() const
			{
				return ConstRow::ConstIterator(line->end());
			}
			typename ConstRow::ConstIterator cbegin() const
			{
				return ConstRow::ConstIterator(line->begin());
			}
			typename ConstRow::ConstIterator cend() const
			{
				return ConstRow::ConstIterator(line->end());
			}
			Iterator begin()
			{
				return Iterator(line->begin());
			}
			Iterator end()
			{
				return Iterator(line->end());
			}
			Row &operator++() noexcept // prefix
			{
				++line;
				return *this;
			}

			Row operator++(int) noexcept // postfix
			{
				return Row(line++);
			}
			Row &operator--() noexcept // prefix
			{
				--line;
				return *this;
			}
			Row operator--(int) noexcept // postfix
			{
				return Row(line--);
			}
			Row &next()
			{
				return ++(*this);
			}
			Row &back()
			{
				return --(*this);
			}
			Row operator+(const typename std::vector<std::vector<T>>::iterator::difference_type &d) const noexcept
			{
				return Row(line + d);
			}
			Row operator-(const typename std::vector<std::vector<T>>::iterator::difference_type &d) const noexcept
			{
				return Row(line - d);
			}
			Row &operator+=(const typename std::vector<std::vector<T>>::iterator::difference_type &d) noexcept
			{
				line += d;
				return *this;
			}
			Row &operator-=(const typename std::vector<std::vector<T>>::iterator::difference_type &d) noexcept
			{
				line -= d;
				return *this;
			}
			bool operator==(const ConstRow &l) const
			{
				return line == l.line;
			}
			bool operator!=(const ConstRow &l) const
			{
				return line != l.line;
			}
			bool operator>=(const ConstRow &l) const
			{
				return line >= l.line;
			}
			bool operator<=(const ConstRow &l) const
			{
				return line <= l.line;
			}
			bool operator>(const ConstRow &l) const
			{
				return line > l.line;
			}
			bool operator<(const ConstRow &l) const
			{
				return line < l.line;
			}
		};
		class Column;
		class ConstColumn
		{
			typename std::vector<std::vector<pointer>>::const_iterator column;
			explicit ConstColumn(typename std::vector<std::vector<pointer>>::const_iterator iter)
				: column(iter) {}
			friend class Matrix<T>;
			friend class Column;
		public:
			class ConstIterator
			{
				typename std::vector<pointer>::const_iterator iterator;
				explicit ConstIterator(typename std::vector<pointer>::const_iterator iter)
					: iterator(iter) {}
				friend class Column;
				friend class ConstColumn;
				friend class Column::Iterator;
			public:
				ConstIterator &next()
				{
					return ++(*this);
				}
				ConstIterator &back()
				{
					return --(*this);
				}
				ConstIterator &operator++() // prefix
				{
					++iterator;
					return *this;
				}
				ConstIterator operator++(int) // postfix
				{
					return ConstIterator(iterator++);
				}
				ConstIterator &operator--() // prefix
				{
					--iterator;
					return *this;
				}
				ConstIterator operator--(int) // postfix
				{
					return ConstIterator(iterator--);
				}
				ConstIterator operator+(long long d) const
				{
					return ConstIterator(iterator + d);
				}
				ConstIterator operator-(long long d) const
				{
					return ConstIterator(iterator - d);
				}
				ConstIterator &operator+=(long long d)
				{
					iterator += d;
					return *this;
				}
				ConstIterator &operator-=(long long d)
				{
					iterator -= d;
					return *this;
				}
				const_reference operator*() const
				{
					return **iterator;
				}
				const_pointer operator->() const
				{
					return *iterator;
				}
				bool operator==(const ConstIterator &const_iterator) const
				{
					return iterator == const_iterator.iterator;
				}
				bool operator!=(const ConstIterator &const_iterator) const
				{
					return iterator != const_iterator.iterator;
				}
				bool operator>=(const ConstIterator &const_iterator) const
				{
					return iterator >= const_iterator.iterator;
				}
				bool operator>(const ConstIterator &const_iterator) const
				{
					return iterator > const_iterator.iterator;
				}
				bool operator<=(const ConstIterator &const_iterator) const
				{
					return iterator <= const_iterator.iterator;
				}
				bool operator<(const ConstIterator &const_iterator) const
				{
					return iterator < const_iterator.iterator;
				}

			};
			size_t size() const
			{
				return column->size();
			}
			ConstIterator begin() const
			{
				return ConstIterator(column->begin());
			}
			ConstIterator end() const
			{
				return ConstIterator(column->end());
			}
			ConstIterator cbegin() const
			{
				return ConstIterator(column->begin());
			}
			ConstIterator cend() const
			{
				return ConstIterator(column->end());
			}
			const_reference at(const size_t &x) const
			{
				return *column->at(x);
			}
			const_reference operator[](const size_t &x) const
			{
				return *(*column)[x];
			}
			ConstColumn &next()
			{
				return ++(*this);
			}
			ConstColumn &back()
			{
				return ++(*this);
			}
			ConstColumn &operator++() // prefix
			{
				++column;
				return *this;
			}
			ConstColumn operator++(int) // postfix
			{
				return ConstColumn(column++);
			}
			ConstColumn &operator--() // prefix
			{
				--column;
				return *this;
			}
			ConstColumn operator--(int) // postfix
			{
				return ConstColumn(column--);
			}
			ConstColumn operator+(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) const noexcept
			{
				return ConstColumn(column + d);
			}
			ConstColumn operator-(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) const noexcept
			{
				return ConstColumn(column - d);
			}
			ConstColumn &operator+=(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) noexcept
			{
				column += d;
				return *this;
			}
			ConstColumn &operator-=(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) noexcept
			{
				column -= d;
				return *this;
			}
			bool operator==(const ConstColumn &const_column) const
			{
				return column == const_column.column;
			}
			bool operator!=(const ConstColumn &const_column) const
			{
				return column != const_column.column;
			}
			bool operator>=(const ConstColumn &const_column) const
			{
				return column >= const_column.column;
			}
			bool operator>(const ConstColumn &const_column) const
			{
				return column > const_column.column;
			}
			bool operator<=(const ConstColumn &const_column) const
			{
				return column <= const_column.column;
			}
			bool operator<(const ConstColumn &const_column) const
			{
				return column < const_column.column;
			}

		};
		class Column
		{
			typename std::vector<std::vector<pointer>>::iterator column;
			Column(typename std::vector<std::vector<pointer>>::iterator iter)
				: column(iter) {}
			friend class Matrix<T>;
		public:
			class Iterator
			{
				typename std::vector<pointer>::iterator iterator;
				Iterator(typename std::vector<pointer>::iterator iter)
					: iterator(iter) {}
				friend class Column;
			public:
				operator typename ConstColumn::ConstIterator() const
				{
					return ConstColumn::ConstIterator(iterator);
				}
				Iterator &next()
				{
					return ++(*this);
				}
				Iterator &back()
				{
					return --(*this);
				}
				Iterator &operator++() // prefix
				{
					++iterator;
					return *this;
				}
				Iterator operator++(int) // postfix
				{
					return Iterator(iterator++);
				}
				Iterator &operator--() // prefix
				{
					--iterator;
					return *this;
				}
				Iterator operator--(int) // postfix
				{
					return Iterator(iterator--);
				}
				Iterator operator+(long long d) const
				{
					return Iterator(iterator + d);
				}
				Iterator operator-(long long d) const
				{
					return Iterator(iterator - d);
				}
				Iterator &operator+=(long long d)
				{
					iterator += d;
					return *this;
				}
				Iterator &operator-=(long long d)
				{
					iterator -= d;
					return *this;
				}
				reference operator*()
				{
					return **iterator;
				}
				const_reference operator*() const
				{
					return **iterator;
				}
				pointer operator->()
				{
					return *iterator;
				}
				const_pointer operator->() const
				{
					return *iterator;
				}
				bool operator==(const typename ConstColumn::ConstIterator &const_iterator) const
				{
					return iterator == const_iterator.iterator;
				}
				bool operator!=(const typename ConstColumn::ConstIterator &const_iterator) const
				{
					return iterator != const_iterator.iterator;
				}
				bool operator>=(const typename ConstColumn::ConstIterator &const_iterator) const
				{
					return iterator >= const_iterator.iterator;
				}
				bool operator>(const typename ConstColumn::ConstIterator &const_iterator) const
				{
					return iterator > const_iterator.iterator;
				}
				bool operator<=(const typename ConstColumn::ConstIterator &const_iterator) const
				{
					return iterator <= const_iterator.iterator;
				}
				bool operator<(const typename ConstColumn::ConstIterator &const_iterator) const
				{
					return iterator < const_iterator.iterator;
				}
			};
			size_t size() const
			{
				return column->size();
			}
			Iterator begin()
			{
				return Iterator(column->begin());
			}
			Iterator end()
			{
				return Iterator(column->end());
			}
			typename ConstColumn::ConstIterator begin() const
			{
				return ConstColumn::ConstIterator(column->begin());
			}
			typename ConstColumn::ConstIterator end() const
			{
				return ConstColumn::ConstIterator(column->end());
			}
			typename ConstColumn::ConstIterator cbegin() const
			{
				return ConstColumn::ConstIterator(column->begin());
			}
			typename ConstColumn::ConstIterator cend() const
			{
				return ConstColumn::ConstIterator(column->end());
			}
			reference at(const size_t &x)
			{
				return *column->at(x);
			}
			const_reference at(const size_t &x) const
			{
				return *column->at(x);
			}
			reference operator[](const size_t &x)
			{
				return *(*column)[x];
			}
			const_reference operator[](const size_t &x) const
			{
				return *(*column)[x];
			}
			operator ConstColumn() const
			{
				return ConstColumn(column);
			}
			Column &next()
			{
				return ++(*this);
			}
			Column &back()
			{
				return ++(*this);
			}
			Column &operator++() // prefix
			{
				++column;
				return *this;
			}
			Column operator++(int) // postfix
			{
				return Column(column++);
			}
			Column &operator--() // prefix
			{
				--column;
				return *this;
			}
			Column operator--(int) // postfix
			{
				return Column(column--);
			}
			Column operator+(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) const noexcept
			{
				return Column(column + d);
			}
			Column operator-(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) const noexcept
			{
				return Column(column - d);
			}
			Column &operator+=(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) noexcept
			{
				column += d;
				return *this;
			}
			Column &operator-=(const typename std::vector<std::vector<pointer>>::iterator::difference_type &d) noexcept
			{
				column -= d;
				return *this;
			}
			bool operator==(const ConstColumn &const_column) const
			{
				return column == const_column.column;
			}
			bool operator!=(const ConstColumn &const_column) const
			{
				return column != const_column.column;
			}
			bool operator>=(const ConstColumn &const_column) const
			{
				return column >= const_column.column;
			}
			bool operator>(const ConstColumn &const_column) const
			{
				return column > const_column.column;
			}
			bool operator<=(const ConstColumn &const_column) const
			{
				return column <= const_column.column;
			}
			bool operator<(const ConstColumn &const_column) const
			{
				return column < const_column.column;
			}
		};
		Matrix(const size_t &size_x, const size_t &size_y, const T &sample)
			: lines_(size_y, std::vector<pointer>(size_x, nullptr)),
			columns_(size_x, std::vector<pointer>(size_y, nullptr))
		{
			for (auto &i : lines_)
			{
				for (auto &j : i)
				{
					j = new T(sample);
				}
			}
			init_columns();
		}
		Matrix(const size_t &size_x, const size_t &size_y, T &&sample)
			: lines_(size_y, std::vector<pointer>(size_x, nullptr)),
			columns_(size_x, std::vector<pointer>(size_y, nullptr))
		{
			for (auto &i : lines_)
			{
				for (auto &j : i)
				{
					j = new T(std::move(sample));
				}
			}
			init_columns();
		}
		template<size_t x>
		Matrix(const std::initializer_list<std::array<T, x>> &lst)
		{
			size_t size_y = lst.size();
			for (size_t i = 0; i < size_y; i++)
			{
				lines_.push_back(std::vector<pointer>());
			}
			size_t y = 0;
			for (auto &i : lst)
			{
				for (auto &j : i)
				{
					lines_[y].push_back(new T(j));
				}
				y++;
			}
			size_t size_x = 0;
			if (lst.size() != 0)
			{
				if (lst.begin()->size() != 0)
				{
					for (auto &i : *lines_.begin())
						size_x++;
				}
			}
			for (size_t i = 0; i < size_x; i++)
			{
				columns_.push_back(std::vector<pointer>(size_y, nullptr));
			}
			init_columns();
		}
		Matrix(const size_t &size_x, const size_t &size_y)
			: lines_(size_y, std::vector<pointer>(size_x, nullptr)),
			columns_(size_x, std::vector<pointer>(size_y, nullptr))
		{

		}
		Matrix(const Matrix<T> &matrix)
			: lines_(matrix.row_count(), std::vector<pointer>(matrix.column_count(), nullptr)),
			columns_(matrix.column_count(), std::vector<pointer>(matrix.row_count(), nullptr))
		{
			for (size_t y = 0; y < matrix.lines_.size(); ++y)
			{
				for (size_t x = 0; x < matrix.lines_[y].size(); ++x)
				{
					lines_[y][x] = new T(*matrix.lines_[y][x]);
				}
			}
			init_columns();
		}
		Matrix(Matrix<T> &&matrix) noexcept
			: lines_(matrix.row_count(), std::vector<pointer>(matrix.column_count(), nullptr)),
			columns_(matrix.column_count(), std::vector<pointer>(matrix.row_count(), nullptr))
		{
			for (size_t y = 0; y < matrix.lines_.size(); ++y)
			{
				for (size_t x = 0; x < matrix.lines_[y].size(); ++x)
				{
					lines_[y][x] = matrix.lines_[y][x];
					matrix.lines_[y][x] = nullptr;
				}
			}
			init_columns();
		}
		Matrix() = default;
		virtual ~Matrix()
		{
			for (auto &line : lines_)
			{
				for (auto &p : line)
				{
					delete p;
				}
			}
		}
		bool empty() const
		{
			return lines_.empty();
		}
		void resize(const size_t &new_column_count, const size_t &new_line_count)
		{
			for (size_t i = new_line_count; i < row_count(); ++i)
			{
				for (size_t j = 0; j < new_column_count; ++j)
				{
					delete lines_[i][j];
				}
			}
			for (size_t j = new_column_count; j < column_count(); ++j)
			{
				for (size_t i = 0; i < row_count(); ++i)
				{
					delete columns_[j][i];
				}
			}
			size_t before_line_count = lines_.size();
			lines_.resize(new_line_count);
			size_t before_column_count = columns_.size();
			columns_.resize(new_column_count);
			for (auto &column : columns_)
			{
				column.resize(new_line_count);
			}
			for (auto &line : lines_)
			{
				line.resize(new_column_count);
			}
			for (size_t y = before_line_count; y < row_count(); ++y)
			{
				for (size_t x = 0; x < column_count(); ++x)
				{
					lines_[y][x] = new T();
					columns_[x][y] = lines_[y][x];
				}
			}
			for (size_t x = before_column_count; x < column_count(); ++x)
			{
				for (size_t y = 0; y < before_line_count; ++y)
				{
					lines_[y][x] = new T();
					columns_[x][y] = lines_[y][x];
				}
			}
		}
		size_t column_count() const
		{
			return columns_.size();
		}
		size_t row_count() const
		{
			return lines_.size();
		}
		ConstRow begin_row() const
		{
			return ConstRow(lines_.begin());
		}
		Row begin_row()
		{
			return Row(lines_.begin());
		}
		ConstRow cbegin_row() const
		{
			return ConstRow(lines_.cbegin());
		}
		ConstRow end_row() const
		{
			return ConstRow(lines_.end());
		}
		Row end_row()
		{
			return Row(lines_.end());
		}
		ConstRow cend_row() const
		{
			return ConstRow(lines_.cend());
		}
		Row row(const size_t &y)
		{
			if (y >= row_count())
				throw std::out_of_range("invalid line index");
			Row iterator = Row(lines_.begin());
			for (size_t i = 0; i < y; i++)
				iterator++;

			return iterator;
		}
		ConstRow row(const size_t &y) const
		{
			if (y >= row_count())
				throw std::out_of_range("invalid line index");
			ConstRow iterator = ConstRow(lines_.begin());
			for (size_t i = 0; i < y; i++)
				iterator++;

			return iterator;
		}
		Column begin_column()
		{
			return Column(columns_.begin());
		}
		ConstColumn begin_column() const
		{
			return ConstColumn(columns_.begin());
		}
		ConstColumn cbegin_column() const
		{
			return ConstColumn(columns_.begin());
		}
		Column end_column()
		{
			return Column(columns_.end());
		}
		ConstColumn end_column() const
		{
			return ConstColumn(columns_.end());
		}
		ConstColumn cend_column() const
		{
			return ConstColumn(columns_.end());
		}
		Column column(const size_t &x)
		{
			if (x >= column_count())
				throw std::out_of_range("invalid line index");
			Column iterator = Column(columns_.begin());
			for (size_t i = 0; i < x; i++)
				iterator++;

			return iterator;
		}
		ConstColumn column(const size_t &x) const
		{
			if (x >= column_count())
				throw std::out_of_range("invalid line index");
			ConstColumn iterator = ConstColumn(columns_.begin());
			for (size_t i = 0; i < x; i++)
				iterator++;

			return iterator;
		}
		Matrix<T> &operator=(const Matrix<T> &matrix)
		{
			for (auto &line : lines_)
			{
				for (auto &i : line)
				{
					delete i;
				}
				line.clear();
			}
			for (auto &column : columns_)
			{
				column.clear();
			}
			lines_.clear();
			columns_.clear();
			columns_ = std::vector<std::vector<pointer>>(matrix.column_count(), std::vector<pointer>(matrix.row_count(), nullptr));
			lines_ = std::vector<std::vector<pointer>>(matrix.row_count(), std::vector<pointer>(matrix.column_count(), nullptr));
			for (size_t y = 0; y < matrix.lines_.size(); ++y)
			{
				for (size_t x = 0; x < matrix.lines_[y].size(); ++x)
				{
					lines_[y][x] = new T(*matrix.lines_[y][x]);
				}
			}
			init_columns();
			return *this;
		}
		Matrix<T> &operator=(Matrix<T> &&matrix) noexcept
		{
			for (auto &line : lines_)
			{
				for (auto &i : line)
				{
					delete i;
				}
				line.clear();
			}
			for (auto &column : columns_)
			{
				column.clear();
			}
			lines_.clear();
			columns_.clear();
			columns_ = std::vector<std::vector<pointer>>(matrix.column_count(), std::vector<pointer>(matrix.row_count(), nullptr));
			lines_ = std::vector<std::vector<pointer>>(matrix.row_count(), std::vector<pointer>(matrix.column_count(), nullptr));
			for (size_t y = 0; y < matrix.lines_.size(); ++y)
			{
				for (size_t x = 0; x < matrix.lines_[y].size(); ++x)
				{
					auto &i = matrix.lines_[y][x];
					lines_[y][x] = i;
					i = nullptr;
				}
			}
			init_columns();
			return *this;
		}
	private:
		void init_columns()
		{
			size_t x = 0;
			if (column_count() == 0)
				return;
			for (size_t y = 0; y != row_count();)
			{
				columns_[x][y] = lines_[y][x];
				if (y == row_count() - 1)
				{
					if (x == lines_[y].size() - 1)
						break;
					++x;
					y = 0;
				}
				else
					y++;
			}
		}

	};
}