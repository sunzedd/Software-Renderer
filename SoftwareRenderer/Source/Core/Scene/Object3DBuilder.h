#pragma once
#include "../Exceptions.h"
#include "../AssetLoader.h"
#include "../Graphics/Mesh.h"

#include "Object3D.h"

namespace core {

enum class Object3DType
{
    Textured
};

class Object3DBuilder
{
public:
    Object3DBuilder();

    void setTexture(const std::string& filepath);
    void setTexture(const std::shared_ptr<sf::Image> texture);

    void setMesh(const std::string& filepath);
    void setMesh(const std::shared_ptr<Mesh> mesh);

    void setShader(const std::shared_ptr<ShaderProgram> shader);

    void setPosition(float x, float y, float z);
    void setRotation(float x, float y, float z);
    void setScale(float x, float y, float z);

    void reset();
    std::shared_ptr<Object3D> getResult();

private:
    std::shared_ptr<Object3D> m_result;
};

} // namespace core