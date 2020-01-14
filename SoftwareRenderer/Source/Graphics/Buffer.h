#pragma once
#include <memory>
#include <assert.h>

namespace Core
{
	template <typename T>
	class Buffer
	{
	public:
		Buffer(int width, int height);
		virtual ~Buffer();

		T get(int x, int y) const;
		void set(int x, int y, T value);

		virtual void clear();
		void fill(T value);

	protected:
		std::unique_ptr<T[]> m_pData;
		int m_width;
		int m_height;
	};
}

#include "Buffer.hpp"

