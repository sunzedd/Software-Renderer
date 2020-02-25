#pragma once
#include "../IShaderProgram.h"

namespace Core
{
	class PointLightShader : public IShaderProgram
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
			float distance = v_to_light.length();
			Vec3 light_unit_vec = v_to_light / distance;

			float att = 1 / (distance * linear_attentuation + quadratic_attentuation * distance * distance + const_attentuation);
			//float att = 1 / distance;

			float d1 = att * Vec3(out.n).dot(light_unit_vec);
			float d2 = Vec3(out.n).dot(lightDir) / 3;

			out.intensity = std::max(0.0f, d1 + d2);

			return out;
		}

		Vec4 pixelShader(const VSO& interpolated) override
		{
			Vec4 out = (ambient + interpolated.color * interpolated.intensity).saturate();

			return out;
		}

		void bindLightPosition(const Vec3& pos)
		{
			light_pos = pos;
		}

	protected:
		Vec3 light_pos;
		float linear_attentuation = 0.7f;
		float quadratic_attentuation = 0.619f;
		float const_attentuation = 0.382f;
		Vec4 ambient = { 0.0, 0.0, 0.05, 1.0 };

		const Vec3 lightDir = { 0, 0, 0 };
	};
}