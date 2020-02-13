#pragma once
#include "../../Core/Graphics/IShaderProgram.h"

namespace cr = Core;

/*
	+---------------------------------------------------------------------------+
	| Gouraud shading															|
	| 2 light sources: directional and point.									|
	| No texturing provided.													|
	+---------------------------------------------------------------------------+
*/

class Shader : public cr::IShaderProgram
{
public:
	cr::Vec3 lightDir;
	cr::Vec3 pointLightSrcPosition;

private:
	cr::Vec4 ambient = { 0.1, 0.1, 0.1, 1.0f };

public:
	cr::VSO vertexShader(const cr::Vertex& v)
	{
		using namespace cr;
		VSO output(v);

		output.posWorld = Vec4(v.pos) * model;
		output.posView = output.posWorld * view;
		output.n *= model;

		Vec3 n = output.n;

		float d = n.dot(-lightDir);
		float intensityDirLight = std::max(0.0f, d);
		Vec4 vertexToLightSrc = (Vec4(pointLightSrcPosition) - output.posWorld).getNormalized();
		float distance = pointLightSrcPosition.length();
		float intensityPointLight = std::max(0.0f, output.n.dot(vertexToLightSrc)) / distance;

		output.intensity = std::min( 1.0f, intensityDirLight + intensityPointLight );
		output.pos = output.posView * proj;

		return output;
	}

	cr::Vec4 pixelShader(const cr::VSO& interpolated)
	{
		cr::Vec4 outputColor = (ambient + interpolated.color * interpolated.intensity).saturate();

		return outputColor;
	}
};