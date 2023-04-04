#include "../Engine.hpp"

namespace rn
{
	std::string RoundedRect::load_shader_file()
	{
		using namespace std::string_literals;
		return	R"(	#version 450

					uniform vec2 ures;
					uniform sampler2D uTexture;
					uniform float radius;
					const vec2 size = vec2(1.0, 1.0);
					float roundedRect(vec2 pos)
					{
					    float r = radius / ures.y;
					    return smoothstep(size.x / 2.0 + r, size.x / 2.0 - r, abs(pos.x)) * 
					           smoothstep(size.y / 2.0 + r, size.y / 2.0 - r, abs(pos.y));    
					}

					layout (location = 0) out vec4 fragColor;

					void main()
					{    
					    vec2 uv = gl_FragCoord.xy/ures - 0.5;
					    float delta = 0.5 / radius;
					    uv.y = - uv.y;
					    vec4 TexCol = texture(uTexture, uv.xy + 0.5);  
					    fragColor = TexCol*smoothstep(0.5 - delta, 0.5 + delta, roundedRect(uv));
					})";
	}

	RoundedRect::RoundedRect(Vec2f size, float radius) : Rect(size), radius(radius)
	{
		shader.loadFromMemory(file, sf::Shader::Fragment);
	}

	RoundedRect::RoundedRect(const Rect& rectangle, float radius): Rect(rectangle), radius(radius)
	{
		shader.loadFromMemory(file, sf::Shader::Fragment);
	}

	RoundedRect::RoundedRect(const RoundedRect& rect): Rect(rect)
	{
		shader.loadFromMemory(file, sf::Shader::Fragment);
		radius = rect.radius;
	}

	RoundedRect::RoundedRect(RoundedRect&& rect) noexcept
	{
		shader.loadFromMemory(file, sf::Shader::Fragment);
		radius = rect.radius;
		rect.radius = 1.f;
		static_cast<Rect &>(*this) = std::move(static_cast<Rect &&>(rect));
	}

	RoundedRect::RoundedRect()
	{
		shader.loadFromMemory(file, sf::Shader::Fragment);
	}

	void RoundedRect::setRadius(float radius)
	{
		this->radius = radius;
	}

	float RoundedRect::getRadius() const
	{
		return radius;
	}

	void RoundedRect::round(float radius)
	{
		this->radius = radius;
	}

	void RoundedRect::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		if (getOutlineThickness() != 0.f)
		{
			RoundedRect outline = { getSize() + Vec2f{getOutlineThickness() * 2, getOutlineThickness() * 2}, getRadius()};
			outline.setFillColor(getOutlineColor());
			outline.move(-getOutlineThickness(), -getOutlineThickness());
			outline.draw(target, states);
		}
		Vec2u s = Vec2u(this->getSize());
		sf::RenderTexture renderer; // rectangle draw's here
		renderer.create(s.x, s.y);
		renderer.clear({ 0, 0, 0, 0 });
		renderer.draw(Rect(*this), getInverseTransform());
		sf::Sprite spr(renderer.getTexture());
		shader.setUniform("ures", getSize());
		shader.setUniform("uTexture", renderer.getTexture());
		shader.setUniform("radius", radius);
			
		sf::RenderTexture rt; // end texture
		rt.create(s.x, s.y);
		rt.clear({ 0, 0, 0, 0 });
		sf::Sprite end_spr(rt.getTexture());
		rt.draw(spr, &shader);
		target.draw(end_spr, states);
	}

	RoundedRect& RoundedRect::operator=(const RoundedRect& rect)
	{
		if (this != &rect)
		{
			radius = rect.radius;
			shader.loadFromMemory(file, sf::Shader::Fragment);
			static_cast<Rect &>(*this) = static_cast<const Rect &>(rect);
		}
		return *this;
	}

	RoundedRect& RoundedRect::operator=(RoundedRect&& rect) noexcept
	{
		if (this != &rect)
		{
			radius = rect.radius;
			shader.loadFromMemory(file, sf::Shader::Fragment);
			static_cast<Rect &>(*this) = std::move(static_cast<Rect &&>(rect));
		}
		return *this;
	}
}
