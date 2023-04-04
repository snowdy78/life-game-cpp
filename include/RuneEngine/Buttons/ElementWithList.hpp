#pragma once
namespace rn
{
	template<class ButtonT, class Element>
	class ElementWithList : public ButtonT
	{
		using EList = ElementList<Element>;
		void reTransform()
		{
			if (is_active)
			{
				Vec2f p = (*get_list_pos)();
				list->setAbsolute(p);
			}
		}
		Vec2f default_list_pos()
		{
			return Vec2f{this->getPosition().x, this->getPosition().y + this->getSize().y} - this->getOrigin();
		}
		bool is_active = false;
		std::function<Vec2f(void)> *get_list_pos = new std::function<Vec2f()>([this]() {return default_list_pos();  });
		EList *list = nullptr;
	public:
		using ButtonT::ButtonT;
		virtual ~ElementWithList() override
		{
			delete get_list_pos;
		}
		void setListPos(std::function<Vec2f(void)> *lst_pos_counter)
		{
			delete get_list_pos;
			get_list_pos = lst_pos_counter;
		}

		void setPosition(const Vec2f &position)
		{
			ButtonT::setPosition(position);
			reTransform();
		}
		void setPosition(float x, float y)
		{
			ButtonT::setPosition(x, y);
			reTransform();
		}
		void setOrigin(const Vec2f &origin)
		{
			ButtonT::setOrigin(origin);
			reTransform();
		}
		void setOrigin(float x, float y)
		{
			ButtonT::setOrigin(x, y);
			reTransform();
		}
		void move(const Vec2f &offset)
		{
			ButtonT::move(offset);
			reTransform();
		}
		void move(float x, float y)
		{
			ButtonT::move(x, y);
			reTransform();
		}
		void setActive(bool condition)
		{
			is_active = condition;
			if (is_active and list == nullptr)
			{
				list = createList();
				reTransform();
			}
			if (!is_active and list != nullptr)
			{
				delete list;
				list = nullptr;
			}
		}
		bool activity() const
		{
			return is_active;
		}
		void start() override
		{
			if (is_active)
			{
				list->start();
			}
		}
		void update() override
		{
			if (is_active)
			{
				list->update();
			}
		}
		void onEvent(sf::Event &event) override
		{
			Vec2f mpos = Vec2f(rn::mouse_position);
			if (this->isKeydown(event.type, mpos) and event.mouseButton.button == sf::Mouse::Left)
			{
				setActive(!is_active);
			}
			else if (is_active)
			{
				list->onEvent(event);
			}
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			target.draw(Button(*this), states);
			if (is_active)
			{
				target.draw(*list, states);
				target.draw(list->scrollbar, states);
			}
		}
		virtual EList *createList() = 0;
	};
}