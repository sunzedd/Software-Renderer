#include "MixedLightShader.h"

namespace Demo
{
	VS_Output MixedLightShader::vertexShader(const vertex& input)
	{
		// Copy input position, normal, ... ect to output.
		VS_Output out(input);

		// Transform vertex position and normal vector to world space(for intensity calculation).
		out.posWorld = out.pos * model;
		out.n *= model;
		out.n = out.n.getNormalized();

		// Transform vertex position to clip (projection) space.
		out.pos = out.posWorld * (view * proj);

		//+------------------- Intensity computation with 2 light sources -------------------+
		vec3 pointLightDirection = vec3(out.posWorld) - pointLightPosition;
		float distanceToPointLight = pointLightDirection.length();
		pointLightDirection.normalize();

		float attenuationFactor = 1.0f / (
			attenuationCoef.constant +
			attenuationCoef.linear * distanceToPointLight +
			attenuationCoef.quadratic * distanceToPointLight * distanceToPointLight);

		float pointLightIntens = calcIntesity(vec3(out.n), pointLightDirection) * attenuationFactor;
		float directLightIntens = calcIntesity(vec3(out.n), directLightDirection);

		pointLightIntens = std::max(0.0f, pointLightIntens);
		directLightIntens = std::max(0.0f, directLightIntens);

		out.intensity = pointLightIntens + directLightIntens;

		return out;
	}

	color4f MixedLightShader::pixelShader(const VS_Output& interpolated)
	{
		color4f pixelColor = ambient + interpolated.color * interpolated.intensity;
		pixelColor.saturate();

		return pixelColor;
	}

	void MixedLightShader::bindPointLightPosition(const vec3& lpos) 
	{
		pointLightPosition = lpos;
	}

	void MixedLightShader::bindDirectLightDirection(const vec3& ldir) 
	{
		directLightDirection = ldir;
	}
}