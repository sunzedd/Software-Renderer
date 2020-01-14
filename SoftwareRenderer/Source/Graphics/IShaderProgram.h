#pragma once
#include "Vertex.h"

namespace Core
{
	class VSO;

	class IShaderProgram
	{
	public:
		virtual VSO vertexShader(const Vertex& v) = 0;
		virtual Vec4 pixelShader(const VSO& interpolated) = 0;
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

	public:
		VSO& operator += (const VSO& rhs);
		VSO& operator -= (const VSO& rhs);
		VSO& operator *= (float val);
		VSO& operator /= (float val);

		friend VSO operator + (const VSO& lhs, const VSO& rhs);
		friend VSO operator - (const VSO& lhs, const VSO& rhs);
		friend VSO operator * (const VSO& vso, float val);
		friend VSO operator / (const VSO& vso, float val);
	};
}