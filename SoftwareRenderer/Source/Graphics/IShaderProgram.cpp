#include "IShaderProgram.h"

namespace Core
{
	VSO& VSO::operator += (const VSO& rhs)
	{
		pos += rhs.pos;
		n += rhs.n;
		uv += rhs.uv;
		color += rhs.color;
		posWorld += rhs.posWorld;
		intensity += rhs.intensity;

		return *this;
	}

	VSO& VSO::operator -= (const VSO& rhs)
	{
		pos -= rhs.pos;
		n -= rhs.n;
		uv -= rhs.uv;
		color -= rhs.color;
		posWorld -= rhs.posWorld;
		intensity -= rhs.intensity;

		return *this;
	}

	VSO& VSO::operator *= (float val)
	{
		pos *= val;
		n *= val;
		uv *= val;
		color *= val;
		posWorld *= val;
		intensity *= val;

		return *this;
	}

	VSO& VSO::operator /= (float val)
	{
		pos /= val;
		n /= val;
		uv /= val;
		color /= val;
		posWorld /= val;
		intensity /= val;

		return *this;
	}

	VSO operator + (const VSO& lhs, const VSO& rhs)
	{
		VSO out(lhs);
		out += rhs;

		return out;
	}

	VSO operator - (const VSO& lhs, const VSO& rhs)
	{
		VSO out(lhs);
		out -= rhs;

		return out;
	}

	VSO operator * (const VSO& vso, float val)
	{
		VSO out(vso);
		out *= val;

		return out;
	}

	VSO operator / (const VSO& vso, float val)
	{
		VSO out(vso);
		out /= val;

		return out;
	}
}