#pragma once

namespace Core
{
	template <typename T>
	class Triangle
	{
	public:
		T v0;
		T v1;
		T v2;

	public:
		Triangle(const T& v0, const T& v1, const T& v2)
			:
			v0(v0), v1(v1), v2(v2)
		{ }
	};
}