#include "PointLightShaderBase.h"

namespace Demo
{
	VS_Output PointLightShaderBase::vertexShader(const vertex& v)
	{
		// Copy input position, normal, ... ect to output.
		VS_Output out(v);

		// Transform vertex position and normal vector to world space(for intensity calculation).
		out.posWorld = out.pos * model;
		out.posView = out.posWorld * view;
		out.n *= model;
		out.n = out.n.getNormalized();

		// Transform vertex position to clip (projection) space.
		out.pos = out.posView * proj;

		//+------------------- Intensity computation with 2 light sources -------------------+
		vec3 pointLightDirection = vec3(out.posWorld) - m_pointLightPosition;
		float distanceToPointLight = pointLightDirection.length();
		pointLightDirection.normalize();

		float attenuationFactor = 1.0f / (
			m_attenuationCoefs.constant +
			m_attenuationCoefs.linear * distanceToPointLight +
			m_attenuationCoefs.quadratic * distanceToPointLight * distanceToPointLight);

		float pointLightIntens = calcIntesity(vec3(out.n), pointLightDirection) * attenuationFactor;
		float directLightIntens = calcIntesity(vec3(out.n), m_directLightDirection) * m_directLightIntensity;

		pointLightIntens = std::max(0.0f, pointLightIntens);
		directLightIntens = std::max(0.0f, directLightIntens);

		out.intensity = pointLightIntens + directLightIntens;

		return out;
	}

	void PointLightShaderBase::setAttenuation(float constant, float linear, float quadratic)
	{
		m_attenuationCoefs.constant = constant;
		m_attenuationCoefs.linear = linear;
		m_attenuationCoefs.quadratic = quadratic;
	}

	void PointLightShaderBase::setAmbient(const vec4& ambient)
	{
		m_ambient = ambient;
	}

	void PointLightShaderBase::setPointLightPosition(const vec3& pos)
	{
		m_pointLightPosition = pos;
	}

	void PointLightShaderBase::setDirectLightDirection(const vec3& dir)
	{
		m_directLightDirection = dir;
	}

	void PointLightShaderBase::setDirectLightIntensity(float intens)
	{
		m_directLightIntensity = intens;
	}
}