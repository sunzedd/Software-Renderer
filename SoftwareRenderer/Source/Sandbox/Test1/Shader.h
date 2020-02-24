#pragma once
#include "../../Core/Graphics/Shaders/DefaultShader.h"

// +-----------------------------------------------------------+
// | Освещение с использованием точечного и направленного
// | источников света.
// +-----------------------------------------------------------+

namespace cr = Core;

typedef cr::Vertex vertex;
typedef cr::VSO vso;
typedef cr::Vec4 vec4;
typedef cr::Vec3 vec3;

namespace Demo
{
	class Shader : public cr::DefaultShader
	{
	private:
		vec4 light_pos = {  0.0f, 0.0f, 0.0f, 1.0f };
		vec4 light_dir = { -1.0f, -1.0f, 0.0f, 0.0f };
		
		vec3 attenuation_coefs = { 1.0f, 0.01f, 0.002f };
		vec4 ambient = { 0.1f, 0.1f, 0.1f, 1.0f};
		float dir_light_resist = 0.7f;

	public:
		vso vertexShader(const vertex& v) override
		{
			vso result(v);

			result.posWorld = vec4(v.pos) * model;
			result.n = result.n * model;
			result.n = result.n.getNormalized();
			result.posView = result.posWorld * view;
			result.pos = result.posView * proj;

			vec3 tmp = result.posWorld - (light_pos);
			vec4 l_to_v_dir = { tmp.x, tmp.y, tmp.z, 0.0f };

			const float l_to_v_dist = l_to_v_dir.length();
			l_to_v_dir = l_to_v_dir.getNormalized();

			float attenuation_factor = attenuation_coefs.x +
				attenuation_coefs.y * l_to_v_dist +
				attenuation_coefs.z * l_to_v_dist * l_to_v_dist;

			float point_i = result.n.dot(-l_to_v_dir) / attenuation_factor;
			float dir_i = result.n.dot(-light_dir) * dir_light_resist;

			point_i = std::max(0.0f, point_i);
			dir_i = std::max(0.0f, dir_i);

			result.intensity = dir_i + point_i;

			return result;
		}

		vec4 pixelShader(const vso& interpolated) override
		{
			vec4 pixel_color = (ambient + interpolated.color * interpolated.intensity).saturate();
			return pixel_color;
		}

		void bindLightPosition(const vec3& lpos)
		{
			light_pos = lpos;
		}
		void bindLightDirection(const vec3& ldir)
		{
			light_dir = ldir;
		}
	};
}