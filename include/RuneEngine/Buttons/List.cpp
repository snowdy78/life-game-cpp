#include "../Engine.hpp"

namespace rn
{

	void List::update_rect_list()
	{
		rect_list.clear();
		for (auto line = begin_row(); line != end_row(); ++line)
		{
			for (auto &rect : line)
			{
				rect_list.push_back(&rect);
			}
		}
	}

	List::ScrollBar::ScrollBar(float length, Table* Base, float bound_height)
	{
		base = Base;
		size = base->getSize();
		bounds = Vec2f(base->getSize().x, bound_height);
		if (base != nullptr)
			absolute_position = Base->getPosition();
		shape = Rect(Vec2f{ length, slider_size() });
		scroll(l);
	}

	void List::ScrollBar::setLength(float length)
	{
		shape.setSize(Vec2f{ length, slider_size()});
	}

	void List::ScrollBar::reTransform()
	{
		size = base->getSize();
		bounds = Vec2f(base->getSize().x, bounds.y);
		shape.setSize({ shape.getSize().x, slider_size()});
		scroll(l);
	}

	void List::ScrollBar::scroll(float k)
	{
		k = std::clamp(k, 0.f, 1.f);
		if (base != nullptr)
		{
			shape.setPosition(getPosition() + Vec2f{ 0, k * (bounds.y - getSize().y) });
			clampPos();
			Vec2f F = { 0, k * (size.y - bounds.y) }; // first element position
			base->setPosition(absolute_position - F);
		}
		l = k;
	}

	void List::ScrollBar::smooth_scroll(float k, std::chrono::milliseconds time)
	{
		k = std::clamp(k, 0.f, 1.f);
		if (base != nullptr)
		{
			move_to(shape, shape.getPosition(), Vec2f{ 0, k * (bounds.y - getSize().y) }, time);
			clampPos();
			Vec2f F = { 0, k * (size.y - bounds.y) }; // first element position
			base->setPosition(absolute_position - F);
		}
		l = k;
	}

	float List::ScrollBar::coefficient() const
	{
		return l;
	}

	void List::ScrollBar::setBounds(const Vec2f& Bounds)
	{
		bounds = Bounds;
		scroll(l);
	}

	const Vec2f& List::ScrollBar::getBounds() const
	{
		return bounds;
	}

	void List::ScrollBar::setPosition(const Vec2f& position)
	{
		Transformable::setPosition(position);
		scroll(l);
	}

	void List::ScrollBar::setPosition(float x, float y)
	{
		Transformable::setPosition(x, y);
		scroll(l);
	}

	void List::ScrollBar::move(float offsetX, float offsetY)
	{
		Transformable::move(offsetX, offsetY);
		scroll(l);
	}

	void List::ScrollBar::move(const Vec2f& offset)
	{
		Transformable::move(offset);
		scroll(l);
	}

	void List::ScrollBar::setFillColor(const sf::Color &color)
	{
		shape.setFillColor(color);
	}

	void List::ScrollBar::setOutlineColor(const sf::Color &color)
	{
		shape.setOutlineColor(color);
	}

	void List::ScrollBar::setOutlineThickness(const float &thickness)
	{
		shape.setOutlineThickness(thickness);
	}

	sf::Color List::ScrollBar::getFillColor() const
	{
		return shape.getFillColor();
	}

	sf::Color List::ScrollBar::getOutlineColor() const
	{
		return shape.getOutlineColor();
	}

	float List::ScrollBar::getOutlineThickness() const
	{
		return shape.getOutlineThickness();
	}

	void List::ScrollBar::setTexture(const sf::Texture *texture, bool reset_rect)
	{
		shape.setTexture(texture, reset_rect);
	}

	void List::ScrollBar::setTextureRect(const sf::IntRect &rect)
	{
		shape.setTextureRect(rect);
	}

	const sf::Texture *List::ScrollBar::getTexture() const
	{
		return shape.getTexture();
	}

	const sf::IntRect &List::ScrollBar::getTextureRect() const
	{
		return shape.getTextureRect();
	}

	const Vec2f& List::ScrollBar::getSize() const
	{
		return shape.getSize();
	}

	float List::ScrollBar::getRatio(const Vec2f& position) const
	{
		return (position.y - getPosition().y) / (bounds.y - shape.getSize().y);
	}

	const Rect& List::ScrollBar::getShape() const
	{
		return shape;
	}

	bool List::ScrollBar::isIntersected(const Vec2f& p) const
	{
		return math::contains(shape, p);
	}

	sf::FloatRect List::ScrollBar::getGlobalBounds() const
	{
		using namespace math_operations;
		return { getPosition() - getOrigin(), Vec2f(bounds) * getScale() };
	}

	sf::FloatRect List::ScrollBar::getLocalBounds() const
	{
		using namespace math_operations;
		return {getOrigin(), Vec2f(bounds)};
	}

	void List::ScrollBar::setAbsolute(const Vec2f& position)
	{
		absolute_position = position;
		scroll(l);
	}

	void List::ScrollBar::setAbsolute(float x, float y)
	{
		absolute_position = Vec2f(x, y);
		scroll(l);
	}

	const Vec2f &List::ScrollBar::getAbsolute() const
	{
		return absolute_position;
	}

	const sf::Transform& List::ScrollBar::getTransform() const
	{
		return shape.getTransform();
	}

	const sf::Transform& List::ScrollBar::getInverseTransform() const
	{
		return shape.getInverseTransform();
	}

	void List::ScrollBar::setTable(Table* table)
	{
		base = table;
		reTransform();
	}

	void List::ScrollBar::resize(const Vec2f& Size)
	{
		size = Size;
		scroll(l);
	}

	float List::ScrollBar::slider_size() const
	{
		return bounds.y * bounds.y / size.y;
	}

	void List::ScrollBar::clampPos()
	{
		shape.setPosition(std::clamp(shape.getPosition().x, getPosition().x, getPosition().x + bounds.x),
		                  std::clamp(shape.getPosition().y, getPosition().y, getPosition().y + bounds.y)
		);
	}

	void List::ScrollBar::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (shape.getSize().y < bounds.y)
			target.draw(shape, states);
				
	}

	List::List(Table &&Table_, float slider_length, float bound_length_y) : Table(std::move(Table_)), scrollbar(slider_length, this, bound_length_y)
	{
		scrollbar.setPosition(this->getPosition().x + this->getSize().x, this->getPosition().y);
		update_rect_list();
	}

	List::List(const List &list) : Table(static_cast<const Table &>(list)), scrollbar(list.scrollbar)
	{
		scrollbar.reTransform();
		update_rect_list();
	}

	List::List(List &&list) noexcept : Table(std::move(static_cast<Table &&>(list))), scrollbar(std::move(list.scrollbar))
	{
		scrollbar.reTransform();
		update_rect_list();
	}

	List::ConstIterator List::begin() const
	{
		return ConstIterator(this, rect_list.begin());
	}

	List::ConstIterator List::cbegin() const
	{
		return ConstIterator(this, rect_list.cbegin());
	}

	List::ConstIterator List::end() const
	{
		return ConstIterator(this, rect_list.end());
	}

	List::ConstIterator List::cend() const
	{
		return ConstIterator(this, rect_list.cend());
	}

	void List::setAbsolute(const Vec2f& position)
	{
		scrollbar.setAbsolute(position);
	}
	void List::setAbsolute(float x, float y)
	{
		scrollbar.setAbsolute(x, y);
	}

	const Vec2f& List::getAbsolute() const
	{
		return scrollbar.getAbsolute();
	}

	sf::FloatRect List::at(const size_t &x, const size_t &y) const
	{
		return this->getCellRect(x, y);
	}


	void List::setCellsSize(const Vec2f &sample)
	{
		Table::setCellsSize(sample);
		scrollbar.reTransform();
		update_rect_list();
	}

	void List::resize(const size_t &width, const size_t &height)
	{
		Table::resize(width, height);
		scrollbar.reTransform();
		update_rect_list();
	}

	void List::setColumnWidth(const size_t &x, float width)
	{
		Table::setColumnWidth(x, width);
		scrollbar.reTransform();
		update_rect_list();
	}

	void List::setRowHeight(const size_t &y, float height)
	{
		Table::setRowHeight(y, height);
		scrollbar.reTransform();
		update_rect_list();
	}

	sf::FloatRect List::getGlobalBounds() const
	{
		using namespace math_operations;
		auto bounds = Table::getGlobalBounds();
		bounds.width += scrollbar.getSize().x * getScale().x;
		return bounds;
	}

	sf::FloatRect List::getLocalBounds() const
	{
		auto bounds = Table::getLocalBounds();
		bounds.width += scrollbar.getSize().x;
		return bounds;
	}

	List &List::operator=(const List &list)
	{
		if (this != &list)
		{
			static_cast<Table &>(*this) = static_cast<const Table &>(list);
			update_rect_list();
			scrollbar = ScrollBar(list.scrollbar);
			scrollbar.setTable(this);
		}
		return *this;
	}

	List &List::operator=(List &&list) noexcept
	{
		if (this != &list)
		{
			static_cast<Table &>(*this) = std::move(static_cast<Table &&>(list));
			update_rect_list();
			scrollbar = ScrollBar(std::move(list.scrollbar));
			scrollbar.setTable(this);
		}
		return *this;
	}

	void List::draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(*this, states);
		target.draw(scrollbar, states);
	}

	List::ConstIterator::ConstIterator(const List* list, const vector_const_iterator& iterator): iterator(iterator), parent(list)
	{}

	size_t List::ConstIterator::position() const
	{
		if (parent == nullptr)
			return -1;
		return std::distance(parent->begin().iterator, iterator);
	}

	size_t List::ConstIterator::coord_x() const
	{
		if (parent == nullptr)
			return -1;
		return position() % parent->getColumnCount();
	}

	size_t List::ConstIterator::coord_y() const
	{
		if (parent == nullptr)
			return -1;
		return (position() - coord_x())/parent->getColumnCount();
	}

	List::ConstIterator& List::ConstIterator::operator++()
	{
		++iterator;
		return *this;
	}

	List::ConstIterator List::ConstIterator::operator++(int)
	{
		return ConstIterator(parent, iterator++);
	}

	List::ConstIterator& List::ConstIterator::operator--()
	{
		--iterator;
		return *this;
	}

	List::ConstIterator List::ConstIterator::operator--(int)
	{
		return ConstIterator(parent, iterator--);
	}

	List::ConstIterator List::ConstIterator::operator+(difference_type d) const
	{
		return ConstIterator(parent, iterator + d);
	}

	List::ConstIterator List::ConstIterator::operator-(difference_type d) const
	{
		return ConstIterator(parent, iterator - d);
	}

	List::ConstIterator& List::ConstIterator::operator+=(difference_type d)
	{
		iterator += d;
		return *this;
	}

	List::ConstIterator& List::ConstIterator::operator-=(difference_type d)
	{
		iterator -= d;
		return *this;
	}

	const sf::FloatRect& List::ConstIterator::operator*() const
	{
		return **iterator;
	}

	const sf::FloatRect* List::ConstIterator::operator->() const
	{
		return *iterator;
	}

	bool List::ConstIterator::operator==(const ConstIterator& i) const
	{
		return iterator == i.iterator or this == &i;
	}

	bool List::ConstIterator::operator!=(const ConstIterator& i) const
	{
		return !(*this == i) or this != &i;
	}

	bool List::ConstIterator::operator>(const ConstIterator& i) const
	{
		return iterator > i.iterator;
	}

	bool List::ConstIterator::operator>=(const ConstIterator& i) const
	{
		return iterator >= i.iterator or this == &i;
	}

	bool List::ConstIterator::operator<(const ConstIterator& i) const
	{
		return iterator < i.iterator;
	}

	bool List::ConstIterator::operator<=(const ConstIterator& i) const
	{
		return iterator <= i.iterator or this == &i;
	}
}
