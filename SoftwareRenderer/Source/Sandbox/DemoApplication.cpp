#include "DemoApplication.h"

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    m_camera.setPosition(core::Vec3(0, 0, 10.0f));
    
    core::Object3DBuilder objectBuilder;
    m_object = objectBuilder.getResult();
}

void DemoApplication::update(unsigned int deltaTime)
{
    m_object->update(deltaTime);
    m_camera.update(deltaTime);
}

void DemoApplication::render()
{
    core::RenderPipeline::instance().beginFrame();

    m_object->setRenderMode(core::RenderMode::FILLED);
    m_object->render(m_camera);
}