#include "Engine.hpp"

namespace rn
{
	Panels::Panel::Panel(Vec2f size, const sf::String &string, const sf::Font &font)
		: Button(size, string, font)
	{

	}

	void Panels::Panel::onEvent(sf::Event& event)
	{
		Vec2f mpos = Vec2f(rn::mouse_position);
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (isKeydown(event.type, mpos))
			{
				panels->choosePanel(this);
			}
		}
	}

	void Panels::Panel::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(Button(*this), states);
		if (content != nullptr)
		{
			target.draw(*content, states);
		}
	}

	void Panels::start()
	{
		for (auto &panel : panels)
		{
			panel->start();
		}
	}

	void Panels::update()
	{
		for (auto &panel : panels)
		{
			panel->update();
		}
	}

	void Panels::onEvent(sf::Event& event)
	{
		for (auto &panel : panels)
			panel->onEvent(event);
		if (choosed != nullptr)
		{
			choosed->content->onEvent(event);
		}
	}

	Panels::Panel*& Panels::at(size_t x)
	{
		return panels.at(x);
	}

	void Panels::choosePanel(Panel* x)
	{
		if (x != choosed)
		{
			if (choosed != nullptr)
			{
				delete choosed->content;
				choosed->content = nullptr;
				choosed->onCancelChoosingPanel();
			}
			choosed = x;
			choosed->onEnterChoosingPanel();
			choosed->content = choosed->getContent();
		}
	}
	void Panels::init(const Vec2f& panel_size, const std::initializer_list<Panel*> panels)
	{
		this->panel_size = panel_size;
		for (auto &panel : this->panels)
		{
			delete panel;
		}
		this->panels = { panels.begin(), panels.end() };
		for (auto &panel : this->panels)
		{
			panel->panels = this;
		}
		resize(panels.size(), 1);
		setCellsSize(panel_size);
	}

	void Panels::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (auto &panel : panels)
		{
			target.draw(*panel, states);
		}
	}
}
