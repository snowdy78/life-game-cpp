#pragma once

namespace rn
{
	template<class PanelType>
	class Panels : public rn::Table, public MonoBehaviour
	{
	public:
		class Panel : public PanelType
		{
		protected:
			Panels<PanelType> *panels = nullptr;
			friend class Panels<PanelType>;
		public:
			explicit Panel(const std::string &string)
				: PanelType(string)
			{

			}
			void onEvent(sf::Event &event) override
			{
				Vec2f mpos = Vec2f(rn::mouse_position);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (PanelType::isKeydown(event.type, mpos))
					{
						panels->choosePanel(this);
					}
				}
				PanelType::onEvent(event);
			}

			virtual typename PanelType::Content *getContent() const = 0;
		private:
			void draw(sf::RenderTarget &target, sf::RenderStates states) const override
			{
				target.draw(PanelType(*this), states);
				if (PanelType::content != nullptr)
				{
					target.draw(*PanelType::content, states);
				}
			}
		};
		
	protected:
		std::vector<Panel *> panels;
		Panel *choosed = nullptr;
		using Iterator = typename std::vector<PanelType *>::iterator;
		using ConstIterator = typename std::vector<PanelType *>::const_iterator;

	public:
		explicit Panels(const std::initializer_list<PanelType *> &panels)
		{
			init(panels);
		}
		Panels() = default;

		Iterator begin() { return panels.begin(); }
		Iterator end() { return panels.end(); }
		ConstIterator begin() const { return panels.begin(); }
		ConstIterator end() const { return panels.end(); }
		ConstIterator cbegin() const { return panels.cbegin(); }
		ConstIterator cend() const { return panels.cend(); }

		void start() override
		{
			for (auto &panel : this->panels)
			{
				panel->start();
			}
			if (this->choosed != nullptr)
			{
				this->choosed->content->start();
			}
		}
		void update() override
		{
			for (auto &panel : this->panels)
			{
				panel->update();
			}
			if (this->choosed != nullptr)
			{
				this->choosed->content->update();
			}
		}
		void onEvent(sf::Event &event) override
		{
			for (auto &panel : this->panels)
				panel->onEvent(event);
			if (this->choosed != nullptr)
			{
				this->choosed->content->onEvent(event);
			}
		}
		size_t getPanelCount() const
		{
			return panels.size();
		}
		Panel *&at(size_t x)
		{
			return this->panels.at(x);
		}
		virtual void onEnterChoosing() {  }
		virtual void onCancelChoosing() {  }
		void choosePanel(Panel *x)
		{
			if (x != this->choosed)
			{
				if (this->choosed != nullptr)
				{
					delete this->choosed->content;
					this->choosed->content = nullptr;
					onCancelChoosing();
				}
				this->choosed = x;
				this->choosed->content = this->choosed->getContent();
				onEnterChoosing();
			}
		}
		const Panel *getChoosed() const
		{
			return choosed;
		}
		void init(const std::initializer_list<PanelType *> panels)
		{
			for (auto panel = this->panels.begin(); panel != this->panels.end(); panel++)
			{
				delete *panel;
				this->panels.erase(panel);
			}
			for (auto &panel : panels)
			{
				this->panels.push_back(dynamic_cast<Panel *>(panel));
			}
			for (auto &panel : this->panels)
			{
				panel->panels = this;
			}
			resize(panels.size(), 1);
			setCellsSize(Panel::getSize());
		}
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override
		{
			for (auto &panel : this->panels)
			{
				target.draw(*panel, states);
			}
		}

	};
}