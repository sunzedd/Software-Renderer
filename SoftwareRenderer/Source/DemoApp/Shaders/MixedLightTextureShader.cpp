#include "MixedLightTextureShader.h"

namespace Demo
{
	MixedLightTextureShader::MixedLightTextureShader()
	{
		m_image = Core::AssetsLoader::loadImage("Assets\\Textures\\quads.jpg");
	}

	color4f MixedLightTextureShader::pixelShader(const VS_Output& interpolated)
	{
		// clamp texture
		float uv_x = std::max(0.0f, interpolated.uv.x);
		float uv_y = std::max(0.0f, interpolated.uv.y);
		uv_x = std::min(uv_x, 1.0f);
		uv_y = std::min(uv_y, 1.0f);

		int x = abs(m_image->getSize().x * uv_x - 1);
		int y = abs(m_image->getSize().y * uv_y - 1);

		sf::Color texel32 = m_image->getPixel(x, y);
		color4f texel4f = Core::Color(texel32.r, texel32.g, texel32.b, texel32.a).toVec4();

		color4f pixelColor = ambient + texel4f * interpolated.intensity;
		pixelColor.saturate();

		return pixelColor;
	}

	void MixedLightTextureShader::bindTexture(std::shared_ptr<sf::Image> image)
	{
		m_image = image;
	}
}