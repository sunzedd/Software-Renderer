#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "DefaultShader.h"
#include "../Color.h"

namespace Core
{
	class TextureShader : public DefaultShader
	{
	public:
		Vec4 pixelShader( const VSO& interpolated ) override
		{
			int x = m_pTexture->getSize().x * interpolated.uv.x;
			int y = m_pTexture->getSize().y * interpolated.uv.y;

			sf::Color texel = m_pTexture->getPixel( x, y );
			Color c( texel.r, texel.g, texel.b, texel.a );

			return c.toVec4();
		}

		void bindTexture(std::shared_ptr<sf::Image> texture)
		{
			m_pTexture = texture;
		}

	private:
		std::shared_ptr<sf::Image> m_pTexture;
	};
}