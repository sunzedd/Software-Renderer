#pragma once
#include "Common.h"
#include "Vertex.h"
#include "Renderer.h"
#include "Triangle.h"

namespace core {

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();

    const std::vector<Vertex>& vertices() const { return m_vertices; }
    const std::vector<unsigned short>& indices() const { return m_indices; }
    const std::vector<Face>& faces() const { return m_faces; }

    std::vector<LineV3> buildNormalIndicatorLinesList(float lineLength) const;

    void setVertexBuffer(const std::vector<Vertex>& vertices);
    void setIndexBuffer(const std::vector<unsigned short>& indices);
    void buildFaces();

    virtual void render() const;

protected:
    std::vector<Vertex> m_vertices;
    std::vector<unsigned short> m_indices;
    std::vector<Face> m_faces;
};

} // namespace core
