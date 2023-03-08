#pragma once
#include "ScrollBar.hpp"


// vertical scroll class specialization
namespace rn
{
	class List : Table
	{
		std::vector<const sf::FloatRect *> rect_list;
		void update_rect_list();
	public:
		class ScrollBar : public sf::Transformable, public sf::Drawable, public ClickableObject
		{
			Rect shape;
			Table *base = nullptr;
			Vec2f default_position;
			Vec2f size;
			Vec2f bounds;
			float l = 0.f;

			// Size - full size of Object
			// Bounds - limit of slider
			explicit ScrollBar(float length, Table *Base, float bound_height);

			void setLength(float length);

		public:
			ScrollBar() = default;

			void scroll(float k);

			void smooth_scroll(float k, std::chrono::milliseconds time);

			float coefficient() const;

			void setBounds(const Vec2f &Bounds);

			const Vec2f &getBounds() const;

			void setPosition(const Vec2f &position);

			void setPosition(float x, float y);

			void move(float offsetX, float offsetY);

			void move(const Vec2f &offset);

			const Vec2f &getScrollPosition() const;

			sf::FloatRect getScrollGlobalBounds() const;

			sf::FloatRect getScrollLocalBounds() const;

			const Vec2f &getSize() const;

			float getRatio(const Vec2f &position) const;

			const Rect &getShape() const;

			bool isIntersected(const Vec2f &p) const override;

			sf::FloatRect getGlobalBounds() const;

			sf::FloatRect getLocalBounds() const;

			void setTablePosition(const Vec2f &position);

			void setTablePosition(float x, float y);

		private:
			void setTable(Table *table);

			void resize(const Vec2f &Size);

			float slider_size() const;

			void clampPos();

			void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
			friend class List;
		};
		List::ScrollBar scrollbar;
		class ConstIterator;
		using Table::getPosition;
		using Table::getOrigin;
		using Table::getScale;
		using Table::getRotation;
		using Table::getTransform;
		using Table::getInverseTransform;
		using Table::setPosition;
		using Table::setOrigin;
		using Table::setScale;
		using Table::setRotation;
		using Table::getSize;
		using Table::getColumnCount;
		using Table::getColumnRect;
		using Table::getRowRect;
		using Table::getRowCount;
		using Table::getCellCount;
		using Table::getCellSize;
		using Table::getCellPosition;
		using Table::getCellRect;
		
		List(Table &&Table_, float slider_length, float bound_length_y);
		List(const List &list);
		List(List &&list) noexcept;
		List() = default;

		ConstIterator begin() const;
		ConstIterator cbegin() const;
		ConstIterator end() const;
		ConstIterator cend() const;

		sf::FloatRect at(const size_t &x, const size_t &y) const;

		void resize(const size_t &width, const size_t &height);

		sf::FloatRect getGlobalBounds() const;
		sf::FloatRect getLocalBounds() const;

		List &operator=(const List &list);
		List &operator=(List &&list) noexcept;

	private:
		
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	public:
		class ConstIterator
		{
			using vector_const_iterator = std::vector<const sf::FloatRect *>::const_iterator;
			vector_const_iterator iterator;
			const List *parent = nullptr;
			explicit ConstIterator(const List *list, const vector_const_iterator &iterator);
			friend class List;
			
		public:
			using difference_type = std::vector<const sf::FloatRect *>::difference_type;
			size_t position() const;

			size_t coord_x() const;

			size_t coord_y() const;

			ConstIterator &operator++() // prefix
			;

			ConstIterator operator++(int) // postfix
			;

			ConstIterator &operator--() // prefix
			;

			ConstIterator operator--(int) // postfix
			;

			ConstIterator operator+(difference_type d) const;

			ConstIterator operator-(difference_type d) const;

			ConstIterator &operator+=(difference_type d);

			ConstIterator &operator-=(difference_type d);

			const sf::FloatRect &operator*() const;

			const sf::FloatRect *operator->() const;

			bool operator==(const ConstIterator &i) const;

			bool operator!=(const ConstIterator &i) const;

			bool operator>(const ConstIterator &i) const;

			bool operator>=(const ConstIterator &i) const;

			bool operator<(const ConstIterator &i) const;

			bool operator<=(const ConstIterator &i) const;
		};
	};

}
