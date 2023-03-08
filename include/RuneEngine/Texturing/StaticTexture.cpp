#include "../Engine.hpp"

namespace rn
{
	StaticTexture::StaticTexture(const std::string &path) : texture(new sf::Texture)
	{
		if (!texture->loadFromFile(path))
		{
			std::cerr << "[FileNotFoundError] " << "'" << path << "' is not correct." << '\n';
			throw;
		}
	}

	StaticTexture::StaticTexture(const StaticTexture& another_texture)
	{
		texture = new sf::Texture(*another_texture.texture);
	}

	StaticTexture::StaticTexture(StaticTexture&& Texture) noexcept
	{
		texture = Texture.texture;
		Texture.texture = nullptr;
	}

	StaticTexture::~StaticTexture()
	{
		delete texture; 
	}

	const sf::Texture& StaticTexture::operator*() const
	{
		return *texture;
	}

	sf::Texture* StaticTexture::operator->() const
	{
		return texture;
	}
}
