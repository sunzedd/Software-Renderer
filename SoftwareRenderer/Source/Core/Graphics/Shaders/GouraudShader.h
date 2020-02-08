#pragma once
#include <memory>
#include <SFML/Graphics.hpp>
#include "DefaultShader.h"
#include "../Color.h"

namespace Core
{
	class GouraudShader : public DefaultShader
	{
	public:
		VSO vertexShader(const Vertex& v) override
		{
			VSO out(v);

			out.posWorld = out.pos * model;
			out.posView = out.posWorld * view;
			out.pos = out.posView * proj;

			out.n *= model;

			out.intensity = std::max(0.0f, -(Vec3(out.n).dot(light_dir)));

			return out;
		}

		Vec4 pixelShader(const VSO& interpolated) override
		{
			return interpolated.color * interpolated.intensity;
		}

		void bindLightDirection(const Vec3& dir)
		{
			light_dir = dir;
		}

	private:
		Vec3 light_dir;
	};
}
