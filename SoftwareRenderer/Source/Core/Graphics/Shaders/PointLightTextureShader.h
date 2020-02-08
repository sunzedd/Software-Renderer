#pragma once
#include <memory>
#include <SFML/Graphics/Image.hpp>
#include "../Color.h"
#include "../IShaderProgram.h"

namespace Core
{
	class PointLightTextureShader : public IShaderProgram
	{
	public:
		VSO vertexShader(const Vertex& v) override
		{
			VSO out(v);

			out.posWorld = out.pos * model;
			out.posView = out.posWorld * view;
			out.pos = out.posView * proj;
			out.n *= model;

			Vec3 v_to_light = Vec4(light_pos) - out.posWorld;
			float dist = v_to_light.length();
			Vec3 dir = v_to_light / dist;

			float att = 1 / (dist * linear_attentuation);
				
			out.intensity = att * std::max(0.0f, Vec3(-out.n).dot(dir));

			return out;
		}

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

			Vec4 out = (ambient + c.toVec4() * interpolated.intensity).saturate();

			return out;
		}

		void bindLightPosition(const Vec3& pos)
		{
			light_pos = pos;
		}

		void bindTexture(std::shared_ptr<sf::Image> texture)
		{
			m_pTexture = texture;
		}

	protected:
		Vec3 light_pos;
		float linear_attentuation = 1.0f;
		float quadratic_attentuation = 0.2f;
		float const_attentuation = 1.0f;
		Vec4 ambient = { 0.05, 0.05, 0.05, 1.0 };

		std::shared_ptr<sf::Image> m_pTexture;
	};
}