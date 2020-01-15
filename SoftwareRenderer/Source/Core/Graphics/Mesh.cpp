#include "Mesh.h"

namespace Core
{
	Mesh::Mesh()
	{ }

	Mesh::~Mesh()
	{ }

	std::shared_ptr<Mesh> Mesh::quad()
	{
		auto quad = std::make_shared<Mesh>();

		quad->m_vertices =
		{
			{ {-0.5f,  0.5f, 0.0f}, {0,0,1,0}, {0.0f,0.0f}, {1,0,0,1} },
			{ { 0.5f,  0.5f, 0.0f}, {0,0,1,0}, {1.0f,0.0f}, {0,1,0,1} },
			{ { 0.5f, -0.5f, 0.0f}, {0,0,1,0}, {1.0f,1.0f}, {0,0,1,1} },
			{ {-0.5f, -0.5f, 0.0f}, {0,0,1,0}, {0.0f,1.0f}, {1,1,0,1} }
		};

		quad->m_indices =
		{
			2, 1, 0,
			0, 3, 2
		};

		return std::move(quad);
	}

	void Mesh::render(RenderPipeline& renderer) const
	{
		renderer.run(m_vertices, m_indices);
	}
}