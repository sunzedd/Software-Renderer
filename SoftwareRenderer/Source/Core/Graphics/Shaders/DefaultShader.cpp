#include "DefaultShader.h"

namespace Core
{
	VSO DefaultShader::vertexShader( const Vertex& v )
	{
		VSO out(v);

		out.posWorld = out.pos * model;
		out.posView = out.posWorld * view;
		out.pos = out.posView * proj;

		out.n *= model;

		return out;
	}
	
	Vec4 DefaultShader::pixelShader( const VSO& interpolated )
	{
		return interpolated.color;
	}
}