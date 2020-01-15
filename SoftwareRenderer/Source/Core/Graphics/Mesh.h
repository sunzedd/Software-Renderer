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
		static std::shared_ptr<Mesh> sphere();
		static std::shared_ptr<Mesh> cylinder();

		const std::vector<Vertex>& vertices() const { return m_vertices; }
		const std::vector<unsigned short>& indices() const { return m_indices; }

		virtual void render(RenderPipeline& renderer) const;

	protected:
		std::vector<Vertex> m_vertices;
		std::vector<unsigned short> m_indices;
	};
}