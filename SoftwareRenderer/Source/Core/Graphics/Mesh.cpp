#include "Mesh.h"

namespace core {

Mesh::Mesh()
{ }

Mesh::~Mesh()
{ }

std::vector<LineV3> Mesh::buildNormalIndicatorLinesList(float lineLength) const
{
    std::vector<LineV3> normalLines;
    normalLines.reserve(m_vertices.size());

    for (const auto& v : m_vertices)
    {
        Vec3 n = v.n;

        LineV3 l(v.pos, v.pos + n * lineLength);

        normalLines.push_back(l);
    }

    return normalLines;
}

void Mesh::render() const
{
    RenderPipeline::instance().drawIndexedTriangles(m_vertices, m_indices);
}

void Mesh::setVertexBuffer(const std::vector<Vertex>& vertices)
{
    m_vertices = vertices;
}

void Mesh::setIndexBuffer(const std::vector<unsigned short>& indices)
{
    m_indices = indices;
}

} // namespace core
