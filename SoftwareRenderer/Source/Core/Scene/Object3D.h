    #pragma once
#include "../Graphics/Renderer.h"
#include "../Graphics/Mesh.h"
#include "../Graphics/Shader.h"
#include "../AssetLoader.h"
#include "Object3DBase.h"

namespace core {

class Object3D : public Object3DBase
{
public:
    Object3D();

    void render(const ICamera& camera) const override;
    void update(unsigned int deltaTime) override;

    virtual void move(const Vec3& delta) override;
    virtual void rotate(const Vec3& angles) override;
    virtual void scale(const Vec3& scale) override;

    virtual void setPosition(const Vec3& position) override;
    virtual void setRotation(const Vec3& angles) override;
    virtual void setScale(const Vec3& scale) override;

    void setShader(std::shared_ptr<Shader> shader);
    void setMesh(std::shared_ptr<const Mesh> mesh);
    void setTexture(std::shared_ptr<const sf::Image> texture);

protected:
    std::shared_ptr<const Mesh> m_mesh;
    std::shared_ptr<const sf::Image> m_texture;
    std::shared_ptr<Shader> m_shader;
};

} // namespace core