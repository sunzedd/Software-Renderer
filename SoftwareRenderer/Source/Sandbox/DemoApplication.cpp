#include "DemoApplication.h"

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    _initScene();
}

void DemoApplication::update(unsigned int deltaTime)
{
    _updateSceneLogic(deltaTime);

    m_lighter->update(deltaTime);
    m_camera.update(deltaTime);

    for (auto& object : m_objects)
    {
        object.second->update(deltaTime);

        auto shader = std::dynamic_pointer_cast<GouraudTextureShader>(
            object.second->getShader());
        shader->pointLightPosition = m_lighter->getTransform().getPosition();
    }
}

void DemoApplication::render()
{
    core::RenderPipeline::instance().beginFrame();

    for (auto& object : m_objects)
    {
        object.second->render(m_camera);
    }

    m_lighter->render(m_camera);
}

void DemoApplication::_initScene()
{
    m_camera.setPosition(core::Vec3(0, 0, 10.0f));

    core::Object3DBuilder objectBuilder;

    // lighter
    objectBuilder.setMesh("assets\\Meshes\\sphere.obj");
    objectBuilder.setPosition(-3, 2, 0);
    objectBuilder.setScale(0.1f, 0.1f, 0.1f);
    auto lighterObject = objectBuilder.getResult();

    // sphere
    objectBuilder.reset();
    objectBuilder.setShader(std::make_shared<GouraudTextureShader>());
    objectBuilder.setMesh("assets\\Meshes\\sphere.obj");
    auto sphereObject = objectBuilder.getResult();

    // cube
    objectBuilder.reset();
    objectBuilder.setPosition(-3, 0, 3);
    objectBuilder.setShader(std::make_shared<GouraudTextureShader>());
    objectBuilder.setTexture(core::AssetLoader::loadImage("assets\\Textures\\box.jpg"));
    auto cubeObject = objectBuilder.getResult();


    m_lighter = lighterObject;
    m_objects.insert(std::make_pair("sphere", std::move(sphereObject)));
    m_objects.insert(std::make_pair("cube", std::move(cubeObject)));
}

void DemoApplication::_updateSceneLogic(unsigned int deltaTime)
{
    const float speed = deltaTime * 0.0005;

    m_objects.find("cube")->second->getTransform().rotate(core::Vec3(1, 1, 1) * speed);
    m_lighter->getTransform().move(core::Vec3::right() * speed);
}