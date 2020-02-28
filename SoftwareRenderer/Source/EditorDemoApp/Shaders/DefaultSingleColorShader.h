#include "../../Core/Graphics/IShaderProgram.h"

namespace Demo
{
	using vec3 = Core::Vec3;
	using vec4 = Core::Vec4;
	using VS_Output = Core::VSO;
	using vertex = Core::Vertex;
	using color4f = Core::Vec4;

	class DefaultSingleColorShader : public Core::IShaderProgram
	{
	public:
		DefaultSingleColorShader(const color4f& _color)
			:
			color(_color)
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
			return color;
		}

		void bindColor(const color4f& _color)
		{
			color = _color;
		}

	private:
		color4f color;
	};
}