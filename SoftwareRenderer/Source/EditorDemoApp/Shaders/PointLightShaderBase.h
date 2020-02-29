#pragma once
#include "../../Core/Graphics/IShaderProgram.h"
#include "../CoreAliases.h"

namespace Demo
{
	class PointLightShaderBase : public Core::IShaderProgram
	{
	public:
		VS_Output vertexShader(const vertex& v) override;
		virtual color4f pixelShader(const VS_Output& interpolated) = 0;

		void setAttenuation(float constant, float linear, float quadratic);
		void setAmbient(const vec4& ambient);
		void setPointLightPosition(const vec3& pos);
		void setDirectLightDirection(const vec3& dir);
		void setDirectLightIntensity(float intens);

	protected:
		vec3 m_pointLightPosition;
		vec3 m_directLightDirection = { -1.0f, -1.0f, 0.0f };
		vec4 m_ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
		float m_directLightIntensity = 0.5f;
		struct
		{
			float constant    = 1.0f;
			float linear	  = 0.01f;
			float quadratic   = 0.002f;
		}
		m_attenuationCoefs;
	};
}