#pragma once
namespace lg
{
	class Options : public rn::MenuBranch
	{
		class Parameter : public lg::Button
		{
		public:
			explicit Parameter(const Vec2f &size, const std::string &str)
				: lg::Button(size, str)
			{
				setOutlineThickness(getOutlineThickness());
				setOutlineColor(button_text_color);
			}
			static float getOutlineThickness()
			{
				return 1.f;
			}
			~Parameter() override = 0;
		};
		class Button : public Parameter, public rn::MonoBehaviour
		{
			using Parameter::setSize;
		public:
			using MonoBehaviour::update;
			explicit Button(const std::string &string = "")
				: Parameter(getSize(), string)
			{}
			void update_size()
			{
				setSize(getSize());
			}
			void setChoosing(bool condition)
			{
				if (condition)
				{
					setFillColor(hold_button_color);
					content.setFillColor(hold_button_text_color);
				}
				else 
				{
					setFillColor(button_color);
					content.setFillColor(button_text_color);
				}
			}
			static Vec2f getSize()
			{
				Vec2f res = Vec2f(rn::Settings::getResolution());
				return { res.x / 6.f, res.y / 14.f };
			}
		};
		class ParameterButton : public Button
		{
			inline static sf::RenderWindow *window = nullptr;
		public:
			explicit ParameterButton(const std::string &string)
				:
				Button(string)
			{
			}
			explicit ParameterButton()
				:
				Button( "")
			{
			}

			static void setWindow(sf::RenderWindow *win)
			{
				window = win;
			}
			virtual void save() = 0;
		};
		class ParameterName : public Parameter
		{
			using Parameter::setSize;
		public:
			ParameterName(const std::string &value)
				:
				Parameter(getSize(), value)
			{
			}
			void update_size()
			{
				setSize(getSize());
			}
			static Vec2f getSize()
			{
				Vec2f res = Vec2f{ rn::Settings::getResolution() };
				return { res.x / 2.5f, ParameterButton::getSize().y };
			}
		};
		class ButtonList : public rn::ElementList<Button>
		{
		public:
			ButtonList(size_t button_count)
				: ElementList(button_count, Button::getSize() + Vec2f{0, 1}, (Button::getSize().y + Button::getOutlineThickness())*3.f)
			{
				scrolling_speed = 8;
				scrollbar.setFillColor(button_color);
				scrollbar.setOutlineThickness(1);
				scrollbar.setOutlineColor(button_text_color);
			}
		};
		
		class ButtonWithList : public rn::ElementWithList<ParameterButton, Button>
		{
			using Base = rn::ElementWithList<ParameterButton, Button>;
		public:
			ButtonWithList(const std::string &str)
				: Base(str)
			{
				setListPos(new std::function([this]()
				{
					return getPosition() + Vec2f(getSize().x + getOutlineThickness(), 0) - getOrigin();
				}));
			}
		};
		class ResolutionViewer : public ButtonWithList
		{
			class ListOfResolutions : public ButtonList
			{
				ResolutionViewer *resolution_viewer;
				
			public:
				inline static const std::vector<Vec2u> resolutions_4x3 = {
						{1024, 768},
						{1400, 1050},
						{1600, 1200},
						{2048, 1536},
						{3200, 2400}
				};
				inline static const std::vector<Vec2u> resolutions_16x9 = {
						{1280, 720},
						{1366, 768},
						{1600, 900},
						{1920, 1080},
						{2560, 1440},
						{3840, 2160}
				};
				inline static const std::vector<Vec2u> resolutions_16x10 = {
					{1440, 900},
					{1536, 960},
					{1680, 1050},
					{1920, 1200},
					{2048, 1080},
					{4096, 2160}
				};
				static std::vector<Vec2u> getResolutions()
				{
					auto mode = sf::VideoMode::getDesktopMode();
					auto screen_resolution = Vec2u(mode.width, mode.height);
					screen_ratio = { screen_resolution.x/std::gcd(screen_resolution.x, screen_resolution.y), screen_resolution.y/std::gcd(screen_resolution.x, screen_resolution.y) };
					auto f = [&screen_resolution](const std::vector<Vec2u> &resolutions_)
					{
						std::vector resolutions = resolutions_;
						auto i = std::find(resolutions.begin(), resolutions.end(), screen_resolution);
						if (i == resolutions.end())
						{
							auto iter = resolutions.begin();
							while (iter != resolutions.end() and screen_resolution.x > iter->x)
							{
								iter++;
							}
							resolutions.insert(iter, screen_resolution);
						}
						return resolutions;
					};
					if (screen_ratio == Vec2u{ 4, 3 })
					{
						return f(resolutions_4x3);
					}
					if (screen_ratio == Vec2u{ 16, 9 })
					{
						return f(resolutions_16x9);
					}
					if (screen_ratio == Vec2u(16, 10))
					{
						return f(resolutions_16x10);
					}
					using namespace rn::algorithm;
					return f(resolutions_4x3 + resolutions_16x9 + resolutions_16x10);
				}
				inline static Vec2u screen_ratio;
				inline static const std::vector<Vec2u> settings_resolutions = getResolutions();

				ListOfResolutions(ResolutionViewer *rv)
					:
					ButtonList(settings_resolutions.size()), resolution_viewer(rv)
				{
					auto resolution = settings_resolutions.begin();
					for (auto &button : buttons)
					{
						auto x = std::to_string(resolution->x) + "x" + std::to_string(resolution->y);
						button.content.setString(x);
						resolution++;
					}
				}

				void onEvent(sf::Event &event) override
				{
					Vec2f mpos = Vec2f{ rn::mouse_position };
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						sf::FloatRect list_bounds = {getAbsolute() - getOrigin(), scrollbar.getBounds()};
						if (list_bounds.contains(mpos))
						{
							auto i = settings_resolutions.begin();
							for (auto &button : buttons)
							{
								if (button.isKeydown(event.type, mpos))
								{
									resolution_viewer->chooseResolution(*i);
									return;
								}
								i++;
							}
						}
					}
					if (event.mouseButton.button == sf::Mouse::Left or sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (Clickable::isKeydown(event.type) and !scrollbar.isPushed(event.type, mpos))
						{
							if (!isIntersected(mpos))
							{
								resolution_viewer->setActive(false);
								return;
							}
						}
					}
					ButtonList::onEvent(event);
				}
				
			};

			inline static Vec2u choosen_resolution = rn::Settings::getResolution();
		public:
			ResolutionViewer()
				: ButtonWithList(std::to_string(rn::Settings::getResolution().x) + "x" + std::to_string(rn::Settings::getResolution().y))
			{
			}

			void chooseResolution(const Vec2u &resolution)
			{
				choosen_resolution = resolution;
				content.setString(std::to_string(resolution.x) + "x" + std::to_string(resolution.y));
				setActive(false);
			}
			static Vec2u getChoosenResolution()
			{
				return choosen_resolution;
			}
			void save() override
			{
				rn::Settings::setResolution(choosen_resolution);
			}
			rn::ElementList<Button> *createList() override
			{
				return new ListOfResolutions(this);
			}
		};
		class VsyncSwitcher : public ParameterButton
		{
			inline static bool enabled = rn::Settings::getVsync();
			void reset()
			{
				content.setString(enablenationToString());
			}
			static sf::String enablenationToString()
			{
				return enabled ? "Enabled" : "Disabled";
			}
		public:
			VsyncSwitcher()
				: ParameterButton(enablenationToString())
			{

			}

			static void set(bool x)
			{
				enabled = x;
			}
			static bool get()
			{
				return enabled;
			}
			void save() override
			{
				rn::Settings::setVsync(enabled);
			}

			void onEvent(sf::Event& event) override
			{
				Vec2f mpos = Vec2f(rn::mouse_position);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (isKeydown(event.type, mpos))
					{
						set(!get());
						reset();
					}
				}
			}
		};
		class FramerateLimiter : public ButtonWithList
		{
			class FramerateLimitsList : public ButtonList
			{
				FramerateLimiter *framerate_limiter = nullptr;
			public:

				inline static std::vector<unsigned> limits = {
					59, 60, 100, 120, 144, 240, 360
				};
				
				FramerateLimitsList(FramerateLimiter *fl)
					:
					ButtonList(limits.size()), framerate_limiter(fl)
				{
					auto limit = limits.begin();
					for (auto &button : buttons)
					{
						auto x = std::to_string(*limit);
						button.content.setString(x);
						limit++;
					}
				}

				void onEvent(sf::Event &event) override
				{
					Vec2f mpos = Vec2f{ rn::mouse_position };
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						sf::FloatRect list_bounds = { getAbsolute() - getOrigin(), scrollbar.getBounds() };
						if (list_bounds.contains(mpos))
						{
							auto i = limits.begin();
							for (auto &button : buttons)
							{
								if (button.isKeydown(event.type, mpos))
								{
									framerate_limiter->set(*i);
									framerate_limiter->reset();
									framerate_limiter->setActive(false);
									return;
								}
								i++;
							}
						}
					}
					if (event.mouseButton.button == sf::Mouse::Left or sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (Clickable::isKeydown(event.type) and !scrollbar.isPushed(event.type, mpos))
						{
							if (!isIntersected(mpos))
							{
								framerate_limiter->setActive(false);
								return;
							}
						}
					}
					ButtonList::onEvent(event);
				}
			};
			inline static unsigned limit = rn::Settings::getFramerateLimit();
			void reset()
			{
				content.setString(toString());
			}
			static sf::String toString() 
			{
				return std::to_string(limit);
			}
			
		public:
			FramerateLimiter()
				: ButtonWithList(toString())
			{
				
			}
			
			static void set(unsigned framerate_limit)
			{
				limit = framerate_limit;
			}
			static unsigned get()
			{
				return limit;
			}
			void save() override
			{
				rn::Settings::setFramerateLimit(limit);
			}
			ButtonList* createList() override
			{
				return new FramerateLimitsList(this);
			}
		};
		class WindowModeViewer : public ButtonWithList
		{
			class WindowModeList : public ButtonList
			{
				WindowModeViewer *window_mode_viewer;
			public:
				WindowModeList(WindowModeViewer *wmv)
					: ButtonList(window_modes.size()), window_mode_viewer(wmv)
				{
					auto mode = window_modes.begin();
					for (auto &button : buttons)
					{
						auto &x = mode->second;
						button.content.setString(x);
						mode++;
					}
				}
				void onEvent(sf::Event &event) override
				{
					Vec2f mpos = Vec2f{ rn::mouse_position };
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						sf::FloatRect list_bounds = { getAbsolute() - getOrigin(), scrollbar.getBounds() };
						if (list_bounds.contains(mpos))
						{
							auto i = window_modes.begin();
							for (auto &button : buttons)
							{
								if (button.isKeydown(event.type, mpos))
								{
									window_mode_viewer->set(i->first);
									window_mode_viewer->reset();
									window_mode_viewer->setActive(false);
									return;
								}
								i++;
							}
						}
					}
					if (event.mouseButton.button == sf::Mouse::Left or sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (Clickable::isKeydown(event.type) and !scrollbar.isPushed(event.type, mpos))
						{
							if (!isIntersected(mpos))
							{
								window_mode_viewer->setActive(false);
								return;
							}
						}
					}
					ButtonList::onEvent(event);
				}
			};
			inline const static std::map<unsigned, std::string> window_modes = {
					{sf::Style::Close, "Closed"},
					{sf::Style::Fullscreen, "Fullscreen"},
					{sf::Style::None, "None"},
			};
			inline static unsigned window_mode = rn::Settings::getWindowMode();
			void reset()
			{
				content.setString(toString());
			}
			static sf::String toString()
			{
				return window_modes.at(window_mode);
			}
		public:
			WindowModeViewer()
				: ButtonWithList(toString())
			{
				
			}
			static void set(unsigned mode)
			{
				window_mode = mode;
			}
			static unsigned get()
			{
				return window_mode;
			}
			void save() override
			{
				rn::Settings::setWindowMode(window_mode);
			}
			ButtonList *createList() override
			{
				return new WindowModeList(this);
			}
		};
		class Panel_T : public Button
		{
		public:
			using Button::Button;
			struct Content : sf::Drawable, rn::MonoBehaviour
			{
				Content() = default;
				virtual void update_positions() {};
				virtual void update_sizes() {};
				virtual void save() = 0;
			};
			Content *content = nullptr;
			void save()
			{
				if (content != nullptr)
				{
					content->save();
				}
			}
			void update_positions()
			{
				if (content != nullptr)
					content->update_positions();
			}
			void update_sizes()
			{
				if (content != nullptr)
					content->update_sizes();
			}
		};
		class SettingPanels : public rn::Panels<Panel_T>
		{
		protected:
			void update_positions()
			{
				Vec2f res = Vec2f(rn::Settings::getResolution());
				Table::setPosition(res.x / 6.5f, 0.f);
				for (size_t x = 0; x < panels.size(); x++)
				{
					panels[x]->setPosition(getCellPosition(x, 0));
				}
				if (choosed != nullptr)
					choosed->update_positions();
				accept_button.setPosition(res - accept_button.getSize() - res / 32.f);
				buttons_align.setPosition(res - buttons_align.getSize() - res / 32.f);
				std::vector v = { &accept_button, &ResetToDefault_button };
				for (size_t x = 0; x < buttons_align.getColumnCount(); x++)
				{
					v[x]->setPosition(buttons_align.getCellPosition(x, 0));
				}
			}
			void update_sizes()
			{
				setCellsSize(Panel::getSize());
				for (auto &panel : panels)
				{
					panel->update_size();
				}
				if (choosed != nullptr)
					choosed->update_sizes();
				accept_button.update_size();
				ResetToDefault_button.update_size();
				buttons_align.setCellsSize(ParameterButton::getSize() + Vec2f{ 30, 0 });
			}
		private:
			Button accept_button = Button("Accept");
			Button ResetToDefault_button = Button("Reset");
			rn::Table buttons_align = {2, 1, ParameterButton::getSize() + Vec2f{30, 0}};
			Options *branch = nullptr;
		public:
			explicit SettingPanels(Options *branch, const std::initializer_list<Panel_T *> &panels)
			{
				this->branch = branch;
				init(panels);
				update_positions();
			}
			void onEnterChoosing() override
			{
				choosed->setChoosing(true);
				update_positions();
			}
			void onCancelChoosing() override
			{
				choosed->setChoosing(false);
			}
			
			void setPosition(const Vec2f &position)
			{
				Table::setPosition(position);
				update_positions();
			}
			void onEvent(sf::Event &event) override
			{
				Vec2f mpos = Vec2f(rn::mouse_position);
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					if (accept_button.isKeydown(event.type, mpos) and branch != nullptr)
					{
						for (auto &panel : panels)
						{
							panel->save();
						}
						branch->reopen_window();
						update_sizes();
						update_positions();
						return;
					}
				}
				Panels<Panel_T>::onEvent(event);
			}
			void setPosition(float x, float y)
			{
				Table::setPosition(x, y);
				update_positions();
			}
			void draw(sf::RenderTarget &target, sf::RenderStates states) const override
			{
				target.draw(accept_button, states);
				target.draw(ResetToDefault_button, states);
				for (auto &panel : panels)
				{
					target.draw(*panel, states);
				}
			}
		};
		class VideoSettings : public SettingPanels::Panel
		{
		public:

			struct Content : Panel::Content
			{
				std::vector<ParameterName *> parameter_names = {
					new ParameterName("Resolution"),
					new ParameterName("Vertical synchronization"),
					new ParameterName("Framerate Limit"),
					new ParameterName("Window mode")
				};
				std::vector<ParameterButton *> parameter_buttons = {
					new ResolutionViewer,
					new VsyncSwitcher,
					new FramerateLimiter,
					new WindowModeViewer
				};
				rn::List parameters = {
					{ 2, std::max(parameter_buttons.size(), parameter_names.size()), getSize() },
					20,
					static_cast<float>(rn::Settings::getResolution().y - rn::Settings::getResolution().y) / 7.f };

				Content()
				{
					parameters.setColumnWidth(0, ParameterName::getSize().x);
				}
				~Content() override
				{
					for (auto &name : parameter_names)
						delete name;
					for (auto &button : parameter_buttons)
						delete button;
				}
				void start() override
				{
					for (auto &button : parameter_buttons)
					{
						button->start();
					}
				}
				void update() override
				{
					for (auto &button : parameter_buttons)
					{
						button->update();
					}
				}
				void onEvent(sf::Event& event) override
				{
					for (auto &button : parameter_buttons)
					{
						auto may_be_list_button = dynamic_cast<ButtonWithList *>(button);
						if (may_be_list_button != nullptr)
						{
							if (may_be_list_button->activity())
							{
								may_be_list_button->onEvent(event);
								return;
							}
						}
					}
					for (auto &button : parameter_buttons)
					{
						button->onEvent(event);
					}
				}
				void update_positions() override
				{
					Vec2f res = Vec2f(rn::Settings::getResolution());
					parameters.setPosition(res.x / 6.5f, res.y / 14.f);
					for (size_t y = 0; y < parameter_names.size(); y++)
					{
						parameter_names[y]->setPosition(parameters.getCellPosition(0, y));
					}
					for (size_t y = 0; y < parameter_buttons.size(); y++)
					{
						parameter_buttons[y]->setPosition(parameters.getCellPosition(1, y));
					}
				}
				void update_sizes() override
				{
					Vec2f res = Vec2f(rn::Settings::getResolution());
					for (auto &i : parameter_buttons)
					{
						i->update_size();
					}
					for (auto &i : parameter_names)
					{
						i->update_size();
					}
					parameters.setCellsSize(getSize());
					parameters.setColumnWidth(0, ParameterName::getSize().x);
					parameters.scrollbar.setBounds({ parameters.getSize().x, res.y - res.y / 7.f });
				}
				void save() override
				{
					for (auto &button : parameter_buttons)
					{
						button->save();
					}
				}
				void draw(sf::RenderTarget &target, sf::RenderStates states) const override 
				{
					for (auto &name : parameter_names)
					{
						target.draw(*name);
					}
					for (int i = static_cast<int>(parameter_buttons.size() - 1); i >= 0; i--)
					{
						target.draw(*parameter_buttons[i]);
					}
					target.draw(parameters.scrollbar);
				}
			};

			inline const static std::string name = "Video";
			VideoSettings()
				: Panel(name)
			{
			}
			Panel::Content *getContent() const override
			{
				return new Content;
			}
		};
		class GameSettings : public SettingPanels::Panel
		{
		public:
			struct Content : Panel::Content
			{
				rn::GradientStrip linear_gradient = rn::GradientStrip(ParameterName::getSize(), 
					{
						sf::Color::Red,
						sf::Color::Yellow,
						sf::Color::Green,
						sf::Color::Cyan,
						sf::Color::Blue,
						sf::Color::Magenta
					});
				rn::Table table = {2, 3, Button::getSize()};
				Content()
				{
					table.setColumnWidth(0, ParameterName::getSize().x);
				}
				void update_positions() override
				{
					Vec2f res = Vec2f(rn::Settings::getResolution());
					table.setPosition(res.x / 6.5f, res.y / 14.f);
					linear_gradient.setPosition(table.getCellPosition(0, 1));

				}
				void update_sizes() override
				{
					table.setCellsSize(Button::getSize());
					table.setColumnWidth(0, ParameterName::getSize().x);
					linear_gradient.setSize(ParameterName::getSize());
				}
				void save() override
				{
					
				}
				void onEvent(sf::Event &event) override
				{
					Vec2f mpos = Vec2f(rn::mouse_position);
					if (linear_gradient.isKeydown(event.type, mpos) and event.mouseButton.button == sf::Mouse::Left)
					{
						float t = (linear_gradient.getPosition().x - mpos.x) / linear_gradient.getSize().x;
						sf::Color color = linear_gradient.findColor(t);
					}
				}
				void draw(sf::RenderTarget &target, sf::RenderStates states) const override
				{
					target.draw(linear_gradient, states);
				}
			};
			inline const static std::string name = "Game";
			GameSettings()
				: Panel(name)
			{

			}
			
			Panel::Content *getContent() const override
			{
				return new Content;
			}
		};
		class SoundSettings : public SettingPanels::Panel
		{
			class Content : public Panel::Content
			{
				inline static Vec2f res = Vec2f{rn::Settings::getResolution()};
				class RDRect : public rn::RoundedRect
				{
				public:
					RDRect()
						: RoundedRect(getSize(), 5)
					{
						setOutlineThickness(3);
						setOutlineColor(button_text_color);
						setFillColor(button_color);
					}
					static Vec2f getSize()
					{
						return { res.x / 32.f, res.y / 18.f };
					}
				};
				class Strip : public sf::Drawable, public sf::Transformable
				{
					struct Rounded : rn::RoundedRect
					{
						Rounded()
							: RoundedRect(getSize(), 5)
						{
							setFillColor(button_text_color);
						}
						static Vec2f getSize()
						{
							return RDRect::getSize();
						}
					};
					struct Rectangle : rn::Rect
					{
					private:
						using rn::Rect::setSize;
					public:
						Rectangle(float width)
							: rn::Rect(Vec2f(width - Rounded::getSize().x, res.y / 18.f))
						{
							setFillColor(button_text_color);
						}
						void setWidth(float width)
						{
							setSize(Vec2f(width - Rounded::getSize().x, res.y / 18.f));
						}
					};
					Rounded left_r;
					Rounded right_r;
					Rectangle rect;
				public:
					explicit Strip(float width)
						: rect(width)
					{
						rect.setPosition(left_r.getSize().x/2, 0);
						right_r.setPosition(rect.getPosition().x + rect.getSize().x - left_r.getSize().x/2, 0);
					}
					void setFillColor(const sf::Color &color)
					{
						left_r.setFillColor(color);
						right_r.setFillColor(color);
						rect.setFillColor(color);
					}
					sf::Color getFillColor() const
					{
						return left_r.getFillColor();
					}
					void setWidth(float width)
					{
						rect.setWidth(width);
						rect.setPosition(left_r.getSize().x / 2, 0);
						right_r.setPosition(rect.getPosition().x + rect.getSize().x - left_r.getSize().x / 2, 0);
					}
					void draw(sf::RenderTarget& target, sf::RenderStates states) const override
					{
						states.transform *= getTransform();
						target.draw(left_r, states);
						target.draw(right_r, states);
						target.draw(rect, states);
					}
				};
				rn::CountSlider<RDRect> slider;
				Strip strip = Strip(ParameterName::getSize().x + RDRect::getSize().x);
				Strip progressbar = Strip(0);

				rn::Table table = rn::Table(2, 3);
			public:
				Content()
				{
					res = Vec2f(rn::Settings::getResolution());
					table.setPosition(res.x / 6.5f, res.y / 14.f);
					table.setColumnWidth(0, ParameterButton::getSize().x);
					table.setColumnWidth(1, ParameterName::getSize().x);

					auto slider_cell = table.getCellRect(1, 0);
					auto slider_cell_pos = Vec2f{ slider_cell.left , slider_cell.top };
					slider = rn::CountSlider{ RDRect(), slider_cell_pos + Vec2f{slider_cell.width, 0}};
					strip.setPosition(slider_cell_pos);
					progressbar.setPosition(slider_cell_pos);

					progressbar.setFillColor(rn::math::mix(button_text_color, button_color));
					slider.setPosition(slider_cell_pos);
				}
				void save() override
				{
					float volume = slider.coefficient() * 100.f;
					std::cout << volume << "\n";
					rn::Settings::setMusicVolume(volume);
				}
				void onEvent(sf::Event &event) override
				{
					Vec2f mpos = Vec2f(rn::mouse_position);
					if (event.mouseButton.button == sf::Mouse::Left or sf::Mouse::isButtonPressed(sf::Mouse::Left))
					{
						if (slider.isPushed(event.type, mpos))
						{
							auto t = slider.getRatio(mpos.x - slider.getShape().getSize().x / 2.f, mpos.y);
							slider.slide(t);
							progressbar.setWidth((slider.getShape().getPosition().x + slider.getShape().getSize().x/2) - slider.getPosition().x);
						}
					}
				}
				void draw(sf::RenderTarget &target, sf::RenderStates states) const override
				{
					target.draw(strip, states);
					target.draw(progressbar, states);
					target.draw(slider, states);
				}
				
			};
		public:
			inline const static std::string name = "Sound";
			SoundSettings()
				: Panel(name)
			{}
			Panel::Content *getContent() const override
			{
				return new Content;
			}
		};
		Vec2f res = Vec2f(rn::Settings::getResolution());
		SettingPanels panels = SettingPanels{ this, {new VideoSettings, new GameSettings, new SoundSettings} };
	public:
		Options(sf::RenderWindow &window)
			: MenuBranch(window)
		{
			ParameterButton::setWindow(&window);
		}
		void reopen_window();
		void start() override;
		void update() override;
		
		void onEvent(sf::Event& event) override;
	};
}
