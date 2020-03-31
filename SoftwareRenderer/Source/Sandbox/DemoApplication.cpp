#include "DemoApplication.h"

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    m_camera.setPosition(core::Vec3(0, 0, 10.0f));
    
    core::Object3DBuilder objectBuilder;

    // lighter
    objectBuilder.setMesh("assets\\Meshes\\sphere.obj");
    objectBuilder.setPosition(0, 3, 0);
    objectBuilder.setScale(0.1f, 0.1f, 0.1f);
    m_lighter = objectBuilder.getResult();
    m_objects.push_back(m_lighter);

    // sphere
    objectBuilder.reset();
    objectBuilder.setShader(std::make_shared<GouraudTextureShader>());
    objectBuilder.setMesh("assets\\Meshes\\sphere.obj");
    m_objects.push_back(objectBuilder.getResult());

    // default cube
    objectBuilder.reset();
    objectBuilder.setPosition(-3, 0, 3);
    objectBuilder.setShader(std::make_shared<GouraudTextureShader>());
    m_objects.push_back(objectBuilder.getResult());
}

void DemoApplication::update(unsigned int deltaTime)
{
    m_objects[0]->getTransform().rotate(core::Vec3(0.005f, 0.005f, 0.005f) * deltaTime);
    m_objects[1]->getTransform().move(core::Vec3::right() * deltaTime * 0.001f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
    {
        for (std::shared_ptr<core::Object3D>& obj : m_objects)
            obj->setRenderMode(core::RenderMode::FILLED);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        for (std::shared_ptr<core::Object3D>& obj : m_objects)
            obj->setRenderMode(core::RenderMode::WIREFRAME);
    }

    for (std::shared_ptr<core::Object3D>& obj : m_objects) 
        obj->update(deltaTime);
    m_camera.update(deltaTime);
}

void DemoApplication::render()
{
    core::RenderPipeline::instance().beginFrame();

    for (std::shared_ptr<core::Object3D>& obj : m_objects)
        obj->render(m_camera);
}