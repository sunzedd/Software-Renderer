#pragma once
#include "../IShaderProgram.h"

namespace Core
{
	class DefaultShader : public IShaderProgram
	{
	public:
		virtual VSO vertexShader( const Vertex& v ) override;
		virtual Vec4 pixelShader( const VSO& interpolated ) override;
	};
}
