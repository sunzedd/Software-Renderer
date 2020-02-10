#pragma once
#include "Vertex.h"
#include "RenderPipeline.h"

namespace Core
{
	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh();

		static std::shared_ptr<Mesh> quad();
		static std::shared_ptr<Mesh> cube();

		const std::vector<Vertex>& vertices() const { return m_vertices; }
		const std::vector<unsigned short>& indices() const { return m_indices; }

		void setVertexBuffer(const std::vector<Vertex>& vertices);
		void setIndexBuffer(const std::vector<unsigned short>& indices);

		virtual void render(RenderPipeline& renderer) const;

	protected:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned short> m_indices;
	};
}