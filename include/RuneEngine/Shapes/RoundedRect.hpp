#pragma once
#include <SFML/Graphics.hpp>
#include <fstream>

namespace rn
{
	class RoundedRect : public Rect
	{
		static std::string load_shader_file();
	public:
		RoundedRect(Vec2f size, float radius = 1.f);
		RoundedRect(const Rect &rectangle, float radius = 1.f);
		RoundedRect(const RoundedRect &rect);
		RoundedRect(RoundedRect &&rect) noexcept;
		RoundedRect();
		void setRadius(float radius);
		float getRadius() const;
		void round(float radius);
		RoundedRect &operator=(const RoundedRect &rect);
		RoundedRect &operator=(RoundedRect &&rect) noexcept;
	private:
		mutable sf::Shader shader;
		float radius = 1.f; // round degree
		inline static const std::string file = load_shader_file();
		void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	};

	
}
