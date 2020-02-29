#pragma once
#include "PointLightShaderBase.h"

namespace Demo
{
	class PointLightColorShader : public PointLightShaderBase
	{
	public:
		color4f pixelShader(const VS_Output& interpolated)
		{
			color4f pixelColor = m_ambient + m_color * interpolated.intensity;
			pixelColor.saturate();

			return pixelColor;
		}

		void setColor(const color4f& color)
		{
			m_color = color;
		}

	private:
		color4f m_color;
	};
}