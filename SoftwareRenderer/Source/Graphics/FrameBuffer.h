#pragma once
#include "Buffer.h"
#include "Color.h"

namespace Core 
{
	class FrameBuffer : public Buffer<Color>
	{
	public:
		FrameBuffer(int width, int height)
			:
			Buffer(width, height)
		{ }
		
		const Color* pixels() const
		{
			return m_pData.get();
		}
	};
}