#pragma once

namespace rn
{
	template<class Element>
	class ElementList : public List, public rn::ClickableObject, public rn::MonoBehaviour
	{
		struct Buttons : std::vector<Element>, sf::Drawable, sf::Transformable
		{
			ElementList<Element> *buttonlist = nullptr;
			Buttons(ElementList<Element> *buttonlist, size_t n, const Element &button)
				: std::vector<Element>(n, button), buttonlist(buttonlist)
			{

			}
			const sf::Transform &getTransform() const
			{
				return buttonlist->getTransform();
			}
			const sf::Transform &getInverseTransform() const
			{
				return buttonlist->getInverseTransform();
			}
			void draw(sf::RenderTarget &target, sf::RenderStates states) const override
			{
				for (auto &button : *this)
				{
					target.draw(button, states);
				}
			}
		};
	protected:
		void recount_buttons_position()
		{
			auto rect = List::begin();
			for (auto button = buttons.begin(); button != buttons.end(); button++)
			{
				Vec2f p = getPosition() + Vec2f(rect->left, rect->top);
				button->setPosition(p);
				++rect;
			}
		}
		void reset_clip()
		{
			auto g = getGlobalBounds();
			clipped_buttons.setRect({ getPosition() - getAbsolute(), scrollbar.getBounds() });
		}
		void reTransform()
		{
			recount_buttons_position();
			scrollbar.setPosition(getPosition().x + getSize().x, getPosition().y);
			clipped_buttons.setPosition(getAbsolute() - getOrigin());
			reset_clip();
		}
		Buttons buttons;
		rn::clip<Buttons> clipped_buttons;
	public:
		float scrolling_speed = 8.f;

		ElementList(size_t button_count, Vec2f cell_size, float height)
			:
			List(rn::Table(1, button_count, cell_size), 20, height),
			buttons(this, button_count, Element()),
			clipped_buttons(buttons, scrollbar.getBounds())
		{
			reTransform();
		}
		auto begin()
		{
			return buttons.begin();
		}
		auto begin() const
		{
			return buttons.begin();
		}
		auto cbegin() const
		{
			return buttons.cbegin();
		}
		auto end()
		{
			return buttons.end();
		}
		auto end() const
		{
			return buttons.end();
		}
		auto cend() const
		{
			return buttons.cend();
		}
		
		void setAbsolute(const Vec2f &p)
		{
			List::setAbsolute(p);
			reTransform();
		}
		void setAbsolute(float x, float y)
		{
			List::setAbsolute(x, y);
			reTransform();
		}
		void setOrigin(const Vec2f &origin)
		{
			List::setOrigin(origin);
			reTransform();
		}
		void setOrigin(float x, float y)
		{
			List::setOrigin(x, y);
			reTransform();
		}
		Vec2f getSize() const
		{
			return List::getSize();
		}
		sf::FloatRect getGlobalBounds() const
		{
			return { getPosition() - getOrigin(), getSize() };
		}
		sf::FloatRect getLocalBounds() const
		{
			return { getOrigin(), getSize() };
		}
		void onEvent(sf::Event &event) override
		{
			Vec2f mpos = Vec2f(rn::mouse_position);
			if (event.type == sf::Event::MouseWheelMoved)
			{
				sf::FloatRect list_bounds = { getAbsolute() - getOrigin(), scrollbar.getBounds() };
				if (list_bounds.contains(mpos))
				{
					scrollbar.scroll(
						scrollbar.getRatio(
							{
								scrollbar.getPosition().x,
								scrollbar.getShape().getPosition().y - static_cast<float>(event.mouseWheel.delta) * scrolling_speed
							}));
					recount_buttons_position();
					reset_clip();
				}
			}
			if (event.mouseButton.button == sf::Mouse::Left or sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				if (scrollbar.isPushed(event.type, mpos))
				{
					using namespace std::chrono_literals;
					scrollbar.scroll(scrollbar.getRatio(mpos - scrollbar.getSize() / 2.f));
					recount_buttons_position();
					reset_clip();
				}
			}
		}
		bool isIntersected(const Vec2f &p) const override
		{
			return rn::math::contains(getGlobalBounds(), p);
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			target.draw(clipped_buttons, states);
		}
	};
}