#pragma once
namespace rn
{
	class StaticTexture
	{
		sf::Texture *texture = nullptr;
	public:
		StaticTexture(const std::string &path);

		StaticTexture(const StaticTexture &another_texture);

		StaticTexture(StaticTexture &&Texture) noexcept;

		~StaticTexture();
		const sf::Texture &operator*() const;
		sf::Texture *operator->() const;
		StaticTexture &operator=(const StaticTexture &) = default;
		StaticTexture &operator=(StaticTexture &&) = default;
	};

	
}
