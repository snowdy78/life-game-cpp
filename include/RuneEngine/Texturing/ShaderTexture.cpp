#include "../Engine.hpp"

namespace rn
{
	ShaderTexture::ShaderTexture(const Vec2u &size, const std::string &file, sf::Shader::Type type)
	{
		render_texture->create(size.x, size.y);
		sprite = sf::Sprite(render_texture->getTexture());
		load(file, type);
	}

	void ShaderTexture::render() const
	{
		render_texture->draw(sprite, &shader);
	}

	void ShaderTexture::load(const std::string& file, sf::Shader::Type type)
	{
		shader.loadFromFile(file, type);
	}

	void ShaderTexture::add(const Drawable& drawable, sf::RenderStates states) const
	{
		render_texture->draw(drawable, states);
	}

	void ShaderTexture::fill(sf::Color clr) const
	{
		render_texture->clear(clr);
	}

	const sf::Texture* ShaderTexture::getTexture() const
	{
		return sprite.getTexture();
	}

	sf::Sprite ShaderTexture::getSprite() const
	{
		return sprite;
	}

	sf::Image ShaderTexture::getImage() const
	{
		return sprite.getTexture()->copyToImage();
	}

	void ShaderTexture::draw(sf::RenderTarget& win, sf::RenderStates states) const
	{
		render();
		states.transform *= getTransform();
		win.draw(sprite, states);
	}
}
