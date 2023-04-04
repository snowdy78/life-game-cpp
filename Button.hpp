#pragma once


namespace lg
{
	class Button : public rn::Button
	{
	public:
		explicit Button(const Vec2f &size, const std::string &string);
		explicit Button(const std::string &str);
	};

	
}
