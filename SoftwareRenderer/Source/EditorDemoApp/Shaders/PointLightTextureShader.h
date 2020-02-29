#pragma once
#include <memory>
#include <SFML/Graphics/Image.hpp>
#include "PointLightShaderBase.h"
#include "../../Core/Graphics/Color.h"

namespace Demo
{
	class PointLightTextureShader : public PointLightShaderBase
	{
	public:
		PointLightTextureShader(std::shared_ptr<sf::Image> texture)
			:
			m_texture(texture)
		{ }

		color4f pixelShader(const VS_Output& interpolated)
		{
			// clamp texture
			float uv_x = std::max(0.0f, interpolated.uv.x);
			float uv_y = std::max(0.0f, interpolated.uv.y);
			uv_x = std::min(uv_x, 1.0f);
			uv_y = std::min(uv_y, 1.0f);

			int x = abs(m_texture->getSize().x * uv_x - 1);
			int y = abs(m_texture->getSize().y * uv_y - 1);

			sf::Color texel32 = m_texture->getPixel(x, y);
			color4f texel4f = Core::Color(texel32.r, texel32.g, texel32.b, texel32.a).toVec4();

			color4f pixelColor = m_ambient + texel4f * interpolated.intensity;
			pixelColor.saturate();

			return pixelColor;
		}

		void setTexture(std::shared_ptr<sf::Image> texture)
		{
			m_texture = texture;
		}

	private:
		std::shared_ptr<sf::Image> m_texture;
	};
}