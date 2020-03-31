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
    const std::shared_ptr<Mesh>& getMesh() const;
    const std::shared_ptr<sf::Image>& getTexture() const;

    void setShader(std::shared_ptr<ShaderProgram> shader);
    void setMesh(std::shared_ptr<Mesh> mesh);
    void setTexture(std::shared_ptr<sf::Image> texture);

protected:
    std::shared_ptr<ShaderProgram> m_shader;
    std::shared_ptr<Mesh> m_mesh;
    std::shared_ptr<sf::Image> m_texture;
}; 

} // namespace core