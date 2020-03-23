#pragma once
#include "../Graphics/ShaderProgram.h"
#include "../Graphics/Mesh.h"

#include "CameraBase.h"
#include "GameObject.h"

namespace core
{

class DrawableGameObject : public GameObject
{
public:
    DrawableGameObject(std::shared_ptr<ShaderProgram> shader);
    DrawableGameObject(std::shared_ptr<ShaderProgram> shader,
                       const Vec3& position,
                       const Vec3& rotation,
                       const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f));

    void setShader(std::shared_ptr<ShaderProgram> shader);
    void setTexture(std::shared_ptr<const sf::Image> texture);
    void setMesh(std::shared_ptr<const Mesh> mesh);

    void update(unsigned int deltaTime) override;
    virtual void render(CameraBase& camera);

protected:
    std::shared_ptr<ShaderProgram> m_shader;
    std::shared_ptr<const Mesh> m_mesh;
    std::shared_ptr<const sf::Image> m_texture;
};

}