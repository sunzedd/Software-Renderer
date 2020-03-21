#pragma once
#include "../CoreAliases.h"
#include "../../Core/Graphics/IShaderProgram.h"

namespace Demo
{
	class SingleColorShader : public Core::IShaderProgram
	{
	public:
		SingleColorShader()
			:
			m_color(color4f(0.9f, 0.4f, 0.6f, 1.0f))
		{ }

		SingleColorShader(const color4f& color)
			:
			m_color(color)
		{ }

		VS_Output vertexShader(const vertex& input) override
		{
			VS_Output out(input);

			out.posView = out.pos * (model * view);
			out.pos = out.posView * proj;
			out.intensity = 1.0f;

			return out;
		}

		color4f pixelShader(const VS_Output& interpolated) override
		{
			return m_color;
		}

		void bindColor(const color4f& color)
		{
			m_color = color;
		}

	private:
		color4f m_color;
	};
}