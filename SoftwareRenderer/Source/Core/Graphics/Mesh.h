#pragma once
#include "Common.h"
#include "Vertex.h"
#include "RenderPipeline.h"

namespace Core {

class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	static std::shared_ptr<Mesh> quad();
	static std::shared_ptr<Mesh> cube();

	const std::vector<Vertex>& vertices() const { return m_vertices; }
	const std::vector<unsigned short>& indices() const { return m_indices; }

	std::vector<LineV3> buildNormalIndicatorLinesList(float lineLength) const;

	void setVertexBuffer(const std::vector<Vertex>& vertices);
	void setIndexBuffer(const std::vector<unsigned short>& indices);
	void fillColor(const Vec4& color);

	virtual void render(RenderPipeline& renderer) const;

protected:
	std::vector<Vertex> m_vertices;
	std::vector<unsigned short> m_indices;
};

} // namespace Core