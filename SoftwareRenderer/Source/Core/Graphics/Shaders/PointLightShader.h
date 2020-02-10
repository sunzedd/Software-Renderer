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
			float dist = v_to_light.length();
			Vec3 dir = v_to_light / dist;

			float attentuation = 1.0f / (dist * linear_attentuation + quadratic_attentuation * dist * dist + const_attentuation);
			//float attentuation = 1;
			
			out.intensity = attentuation * std::max(0.0f, Vec3(out.n).dot(dir));

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
		Vec4 ambient = { 0.1, 0.1, 0.1, 1.0 };
	};
}