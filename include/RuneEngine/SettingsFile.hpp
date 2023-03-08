#pragma once

namespace rn
{
	class Settings
	{
		bool vsync; // vertical synchronization
		bool deck_align; // deck left alignment (false - left, true - right)
		Vec2u resolution; // resolution
		unsigned window_mode; // window mode (sf::Style)
		unsigned frame_limit; // frame limit
		float volume; // music volume
		JsonFile json = JsonFile("src", "settings");

	public:

		static void resetToDefault();

		static Vec2u getResolution();
		static unsigned getWindowMode();
		static unsigned getFramerateLimit();
		static float getMusicVolume();
		static bool getVsync();
		static bool getDeckPos();
		static void setResolution(Vec2u);
		static void setWindowMode(unsigned);
		static void setFramerateLimit(unsigned);
		static void setMusicVolume(float);
		static void setVsync(bool);
		// deck left alignment (false - left, true - right)
		static void setDeckPos(bool);
		enum Parameters
		{
			MusicVolume, WindowMode, FramerateLimit, Resolution, Vsync, DeckAlign
		};

	private:
		Settings();
		static std::map<Parameters, std::string> get_params();
		static std::string nameof(Parameters param);
		static JsonFile create_default_settings();
		inline const static JsonFile default_settings = JsonFile(create_default_settings());
	};
}
