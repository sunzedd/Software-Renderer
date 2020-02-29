#pragma once
#include "../CoreAliases.h"
#include "../../Core/Graphics/IShaderProgram.h"

namespace Demo
{
	class SingleColorShader : public Core::IShaderProgram
	{
	public:
		SingleColorShader(const color4f& color)
			:
			m_color(color)
		{ }

		VS_Output vertexShader(const vertex& input) override
		{
			VS_Output out(input);

			out.pos = out.pos * (model * view * proj);
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