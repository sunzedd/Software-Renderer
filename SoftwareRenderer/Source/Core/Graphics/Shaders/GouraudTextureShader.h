#pragma once
#include <memory>
#include "GouraudShader.h"
#include "TextureShader.h"

namespace Core
{
	class GouraudTextureShader : public GouraudShader
	{
	public:
		Vec4 pixelShader(const VSO& interpolated) override
		{
			// clamp texture
			float uv_x = std::max(0.0f, interpolated.uv.x);
			float uv_y = std::max(0.0f, interpolated.uv.y);
			uv_x = std::min(uv_x, 1.0f);
			uv_y = std::min(uv_y, 1.0f);

			int x = abs(m_pTexture->getSize().x * uv_x - 1);
			int y = abs(m_pTexture->getSize().y * uv_y - 1);

			sf::Color texel = m_pTexture->getPixel(x, y);
			Color c(texel.r, texel.g, texel.b, texel.a);

			return c.toVec4() * interpolated.intensity;
		}

		void bindTexture(std::shared_ptr<sf::Image> texture)
		{
			m_pTexture = texture;
		}

	protected:
		std::shared_ptr<sf::Image> m_pTexture;
	};
}
