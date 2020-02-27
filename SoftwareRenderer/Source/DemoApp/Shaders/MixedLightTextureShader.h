#pragma once
#include "MixedLightShader.h"
#include "../../Core/AssetsLoader.h"
#include <sfml/Graphics/Image.hpp>
#include <memory>

namespace Demo
{
	class MixedLightTextureShader : public MixedLightShader
	{
	public:
		MixedLightTextureShader();
		color4f pixelShader(const VS_Output& interpolated) override;
		void bindTexture(std::shared_ptr<sf::Image> image);

	private:
		std::shared_ptr<sf::Image> m_image;
	};
}