#pragma once
#include "../../Core/Graphics/IShaderProgram.h"

namespace Demo
{
	using vec3 = Core::Vec3;
	using vec4 = Core::Vec4;
	using VS_Output = Core::VSO;
	using vertex = Core::Vertex;
	using color4f = Core::Vec4;

	// Two light sources: directional and point.
	class MixedLightShader : public Core::IShaderProgram
	{
	private:
		struct Attenuation
		{
			float constant;
			float linear;
			float quadratic;
		};

	public:
		VS_Output vertexShader(const vertex& input) override;
		color4f pixelShader(const VS_Output& interpolated) override;

		void bindPointLightPosition(const vec3& lpos);
		void bindDirectLightDirection(const vec3& ldir);

	private:
		Attenuation attenuationCoef = { 1.0f, 0.01f, 0.002f };
		vec4 ambient = { 0.1f, 0.1f, 0.1f, 1.0f };
		float dirLightIntensFilterCoef = 0.3f;

		vec3 pointLightPosition;
		vec3 directLightDirection = { -1.0f, -1.0f, 0.0f };
	};
}