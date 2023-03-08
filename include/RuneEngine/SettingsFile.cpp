#include "Engine.hpp"

namespace rn
{
	Vec2u Settings::getResolution()
	{
		return Settings().resolution;
	}
	unsigned Settings::getWindowMode()
	{
		return Settings().window_mode;
	}
	unsigned Settings::getFramerateLimit()
	{
		return Settings().frame_limit;
	}
	float Settings::getMusicVolume()
	{
		return Settings().volume;
	}
	bool Settings::getDeckPos()
	{
		return Settings().deck_align;
	}
	bool Settings::getVsync()
	{
		return Settings().vsync;
	}
	std::map<Settings::Parameters, std::string> Settings::get_params()
	{
		return {
			{MusicVolume, "Music-Volume"},
			{WindowMode, "Window-Mode"},
			{FramerateLimit, "Framerate-Limit"},
			{Resolution, "Resolution"},
			{Vsync, "Vsync"},
			{DeckAlign, "DPos"}
		};
	}
	std::string Settings::nameof(Parameters param)
	{
		auto params = get_params();
		return params.at(param);
	}
	void Settings::setResolution(Vec2u resolution)
	{
		Settings settings;
		settings.json.js[nameof(Resolution)] = { resolution.x, resolution.y };
		settings.json.save();
	}
	void Settings::setFramerateLimit(unsigned limit)
	{
		Settings settings;
		settings.json.js[nameof(FramerateLimit)] = limit;
		settings.json.save();
	}
	void Settings::setMusicVolume(float volume)
	{
		Settings settings;
		settings.json.js[nameof(MusicVolume)] = volume;
		settings.json.save();
	}
	void Settings::setVsync(bool vsync)
	{
		Settings settings;
		settings.json.js[nameof(Vsync)] = vsync;
		settings.json.save();
	}
	void Settings::setDeckPos(bool dpos)
	{
		Settings settings;
		settings.json.js[nameof(DeckAlign)] = dpos;
		settings.json.save();
	}

	void Settings::setWindowMode(unsigned mode)
	{
		Settings settings;
		settings.json.js[nameof(WindowMode)] = mode;
		settings.json.save();
	}

	JsonFile Settings::create_default_settings()
	{
		JsonFile djs("src", "default_settings");
		auto mode = sf::VideoMode::getDesktopMode();
		djs.js[nameof(Resolution)] = { mode.width, mode.height }; // resolution
		djs.js[nameof(Vsync)] = true; // vsync
		djs.js[nameof(DeckAlign)] = true; // deck pos
		djs.js[nameof(MusicVolume)] = 10.f; // music
		djs.js[nameof(FramerateLimit)] = 60; // frame limit
		djs.js[nameof(WindowMode)] = 4; // window mode (sf::Style::Close)
		djs.save();
		return djs;
	}

	Settings::Settings()
	{
		std::vector<std::string> params_name;
		for (auto &p : get_params())
			params_name.push_back(p.second);
		for (auto &name : params_name)
		{
			try
			{
				json.js.at(name);
			}
			catch (Json::out_of_range &err)
			{
				if (err.id == 403)
				{
					try
					{
						json.js[name] = default_settings.js.at(name);
						json.save();
					}
					catch(Json::exception &err1)
					{
						std::cout << err1.what() << "\n";
						throw err1;
					}
				}
				else
				{
					std::cout << err.what() << "\n";
					throw err;
				}
			}
			catch (Json::type_error &err)
			{
				if (err.id == 304)
				{
					try
					{
						json.js[name] = default_settings.js.at(name);
						json.save();
					}
					catch (Json::exception &err1)
					{
						std::cout << err1.what() << "\n";
						throw err1;
					}
				}
				else 
				{
					std::cout << err.what() << "\n";
					throw err;
				}
			}
			catch(Json::exception &err)
			{
				std::cout << err.what() << "\n";
				throw err;
			}
		}

		volume = json.js.at(nameof(MusicVolume));
		auto &jsres = json.js.at(nameof(Resolution));
		resolution = { jsres[0], jsres[1] };
		window_mode = json.js.at(nameof(WindowMode));
		vsync = json.js.at(nameof(Vsync));
		deck_align = json.js.at(nameof(DeckAlign));
		frame_limit = json.js.at(nameof(FramerateLimit));
	}

	void Settings::resetToDefault()
	{
		Settings settings;
		settings.json.js = rn::JsonFile("src", "default_settings.json").js;
		settings.json.save();
	}
}