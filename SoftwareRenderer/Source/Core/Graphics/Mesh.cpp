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

	std::shared_ptr<Mesh> Mesh::cube()
	{
		const float side = 1.0f / 2.0f;
		auto cube = std::make_shared<Mesh>();

		const auto convertUV = [](float u, float v)
		{
			return Vec2{ (u + 1.0f) / 3.0f,v / 4.0f };
		};

		cube->m_vertices =
		{
			{ {-side, -side, -side}, {0,0,-1,0},   {0,0},  {1,0,0,1} },		// 0 far side
			{ {side, -side, -side},	 {0,0,-1,0},   {1,0},  {1,0,0,1} },		// 1
			{ {-side, side, -side},	 {0,0,-1,0},   {0,1},  {1,0,0,1} },		// 2
			{ {side, side, -side},	 {0,0,-1,0},   {1,1},  {1,0,0,1} },		// 3

			{ {-side, -side, side},	 {0,0,1,0},  {0,0},  {0,1,0,1} },		// 4 near side
			{ {side, -side, side},	 {0,0,1,0},  {1,0},  {0,1,0,1} },		// 5
			{ {-side, side, side},	 {0,0,1,0},  {0,1},  {0,1,0,1} },		// 6
			{ {side, side, side},	 {0,0,1,0},  {1,1},  {0,1,0,1} },		// 7

			{ {-side, -side, -side}, {-1,0,0,0},  {0,0},  {0,0,1,1} },		// 8 left side
			{ {-side, side, -side},	 {-1,0,0,0},  {1,0},  {0,0,1,1} },		// 9
			{ {-side, -side, side},	 {-1,0,0,0},  {0,1},  {0,0,1,1} },		// 10
			{ {-side, side, side},	 {-1,0,0,0},  {1,1},  {0,0,1,1} },		// 11

			{ {side, -side, -side},	 {1,0,0,0 },  {0,0},  {1,0,1,1} },		// 12 right side
			{ {side, side, -side},	 {1,0,0,0 },  {1,0},  {1,0,1,1} },		// 13
			{ {side, -side, side},	 {1,0,0,0 },  {0,1},  {1,0,1,1} },		// 14
			{ {side, side, side},	 {1,0,0,0 },  {1,1},  {1,0,1,1} },		// 15

			{ {-side, -side, -side}, {0,-1,0,0},  {0,0},  {1,1,0,1} },		// 16 bottom side
			{ {side, -side, -side},	 {0,-1,0,0},  {1,0},  {1,1,0,1} },		// 17
			{ {-side, -side, side},	 {0,-1,0,0},  {0,1},  {1,1,0,1} },		// 18
			{ {side, -side, side},	 {0,-1,0,0},  {1,1},  {1,1,0,1} },		// 19

			{ {-side, side, -side},	 {0,1,0,0 },  {0,0},  {0,1,1,1} },		// 20 top side
			{ {side, side, -side},	 {0,1,0,0 },  {1,0},  {0,1,1,1} },		// 21
			{ {-side, side, side},	 {0,1,0,0 },  {0,1},  {0,1,1,1} },		// 22
			{ {side, side, side},	 {0,1,0,0 },  {1,1},  {0,1,1,1} }		// 23
		};

		cube->m_indices =
		{
			0,2, 1,    2,3,1,
			4,5, 7,    4,7,6,
			8,10, 9,  10,11,9,
			12,13,15, 12,15,14,
			16,17,18, 18,17,19,
			20,23,21, 20,22,23
		};

		return cube;
	}

	void Mesh::render(RenderPipeline& renderer) const
	{
		renderer.run(m_vertices, m_indices);
	}

	void Mesh::setVertexBuffer(const std::vector<Vertex>& vertices)
	{
		m_vertices = vertices;
	}

	void Mesh::setIndexBuffer(const std::vector<unsigned short>& indices)
	{
		m_indices = indices;
	}

	void Mesh::fillColor(const Vec4& color)
	{
		for (auto& v : m_vertices)
		{
			v.color = color;
		}
	}
}