#pragma once
#include "../Graphics/Mesh.h"
#include "../Graphics/ShaderProgram.h"

#include "Drawable3D.h"

namespace core {

class Object3D : public Drawable3D
{
public:
    virtual void render(const ICamera& camera) override;
    virtual void update(unsigned int deltaTime) override;

    std::shared_ptr<ShaderProgram> getShader();

    void setShader(std::shared_ptr<ShaderProgram> shader);
    void setMesh(std::shared_ptr<Mesh> mesh);

protected:
    std::shared_ptr<ShaderProgram> m_shader;
    std::shared_ptr<Mesh> m_mesh;
}; 

} // namespace core