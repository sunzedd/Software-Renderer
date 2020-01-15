#pragma once
#include "../IShaderProgram.h"

namespace Core
{
	class DefaultShader : public IShaderProgram
	{
	public:
		virtual VSO vertexShader( const Vertex& v ) override;
		virtual Vec4 pixelShader( const VSO& interpolated ) override;

		void bindModelMatrix( const Mat4& m );
		void bindViewMatrix( const Mat4& m );
		void bindProjectionMatrix( const Mat4& m );

	protected:
		Mat4 model;
		Mat4 view;
		Mat4 proj;
	};
}
