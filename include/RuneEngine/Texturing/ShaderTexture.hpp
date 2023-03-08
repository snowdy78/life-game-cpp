#pragma once

namespace rn
{
	class ShaderTexture : public sf::Drawable, public sf::Transformable
	{
		sf::RenderTexture *render_texture = new sf::RenderTexture();
		sf::Shader shader;
		sf::Sprite sprite;
	public:
		ShaderTexture(const Vec2u &size, const std::string &file, sf::Shader::Type type);
		ShaderTexture() = default;
		ShaderTexture(const ShaderTexture &) = delete;
		ShaderTexture(ShaderTexture &&) = delete;
		void render() const;
		~ShaderTexture() override { delete render_texture; }
		void load(const std::string &file, sf::Shader::Type type);

		void add(const Drawable &drawable, sf::RenderStates states = sf::RenderStates::Default) const;

		void fill(sf::Color clr = {0, 0, 0, 255}) const;

		template<class GlslType>
		void setUniform(const std::string &name, const GlslType &Val);
		const sf::Texture *getTexture() const;
		sf::Sprite getSprite() const;
		sf::Image getImage() const;
		ShaderTexture &operator=(const ShaderTexture &) = delete;
		ShaderTexture &operator=(ShaderTexture &&) = delete;
	private:
		void draw(sf::RenderTarget &win, sf::RenderStates states) const override;
	};

	template <class GlslType>
	void ShaderTexture::setUniform(const std::string& name, const GlslType& Val)
	{
		shader.setUniform(name, Val);
	}
}
