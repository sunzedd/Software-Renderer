#include "Object3DBuilder.h"

namespace core {

Object3DBuilder::Object3DBuilder()
{
    m_result = std::make_shared<Object3D>();
}

void Object3DBuilder::setTexture(const std::string& filepath)
{
    try
    {
        auto texture = AssetLoader::loadImage(filepath);
        m_result->setTexture(texture);
    }
    catch(CouldNotLoadAssetException& e)
    {
        auto texture = AssetLoader::loadDefaultImage();
        m_result->setTexture(texture);
    }
}

void Object3DBuilder::setTexture(const std::shared_ptr<sf::Image> texture)
{
    m_result->setTexture(texture);
}

void Object3DBuilder::setMesh(const std::string& filepath)
{
    try
    {
        auto mesh = AssetLoader::loadMesh(filepath);
        m_result->setMesh(mesh);
    }
    catch (CouldNotLoadAssetException & e)
    {
        auto mesh = AssetLoader::loadDefaultMesh();
        m_result->setMesh(mesh);
    }
}

void Object3DBuilder::setMesh(const std::shared_ptr<Mesh> mesh)
{
    m_result->setMesh(mesh);
}

void Object3DBuilder::setShader(const std::shared_ptr<ShaderProgram> shader)
{
    m_result->setShader(shader);
}

void Object3DBuilder::setPosition(float x, float y, float z)
{
    m_result->getTransform().setPosition(Vec3(x, y, z));
}

void Object3DBuilder::setRotation(float x, float y, float z)
{
    m_result->getTransform().setRotation(Vec3(x, y, z));
}

void Object3DBuilder::setScale(float x, float y, float z)
{
    m_result->getTransform().setScale(Vec3(x, y, z));
}

void Object3DBuilder::reset()
{
    m_result.reset();
    m_result = std::make_shared<Object3D>();
}

std::shared_ptr<Object3D> Object3DBuilder::getResult()
{
    if (m_result->getShader() == nullptr)
    {
        m_result->setShader(ShaderProgram::createDefaultShader());
    }
    if (m_result->getMesh() == nullptr)
    {
        m_result->setMesh(AssetLoader::loadDefaultMesh());
    }
    if (m_result->getTexture() == nullptr)
    {
        m_result->setTexture(AssetLoader::loadDefaultImage());
    }

    return m_result;
}

} // namespace core