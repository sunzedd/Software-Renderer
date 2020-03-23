#pragma once
#include <memory>

#include <SFML/Graphics/Image.hpp>
#include "Vertex.h"

namespace core {

class VSO;

class ShaderProgram
{
public:
	virtual VSO vertexShader(const Vertex& v) = 0;
	virtual Vec4 pixelShader(const VSO& interpolated) = 0;

	void bindModelMatrix(const Mat4& m);
	void bindViewMatrix(const Mat4& m);
	void bindProjectionMatrix(const Mat4& m);

	void bindTexture(std::shared_ptr<const sf::Image> texture);

protected:
	float calcIntesity(const Vec3& normal, const Vec3& lightDirection) const;

protected:
	Mat4 model;
	Mat4 view;
	Mat4 proj;
	std::shared_ptr<const sf::Image> m_texture;
};

// Vertex shader output data structure.
class VSO
{
public:
	Vec4 pos;
	Vec4 n;
	Vec2 uv;
	Vec4 color;

	Vec4 posWorld;
	Vec4 posView;
	float intensity;

public:
	VSO(const Vertex& v);

	VSO& operator += (const VSO& rhs);
	VSO& operator -= (const VSO& rhs);
	VSO& operator *= (float val);
	VSO& operator /= (float val);

	friend VSO operator + (const VSO& lhs, const VSO& rhs);
	friend VSO operator - (const VSO& lhs, const VSO& rhs);
	friend VSO operator * (const VSO& vso, float val);
	friend VSO operator / (const VSO& vso, float val);
};

} // namespace core
