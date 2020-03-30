#include "Game.h"

using namespace core;

Game::Game()
{
    initScene();
}

Game::~Game()
{
    delete m_object;
    delete m_camera;
}

void Game::update(unsigned int deltaTime)
{
    m_object->update(deltaTime);
    m_camera->update(deltaTime);
    m_light->update(deltaTime);

    m_object->getTransform().rotation += Vec3::up() * deltaTime / 50.0f;
    
    std::dynamic_pointer_cast<TextureShader>(m_object->getShader())->m_pointLight = m_light;
}

void Game::render()
{
    RenderPipeline::instance().beginFrame();

    m_object->render(*m_camera);
    m_light->render(*m_camera);
}

void Game::initScene()
{
    m_camera = new Camera(Vec3(0.0f, 0.0f, 10.0f), Vec3::forward(), Vec3::up());

    auto shader = std::make_shared<TextureShader>();
    m_object = new DrawableGameObject(shader);
    m_object->setMesh(AssetLoader::loadMesh("Assets\\Meshes\\susann.obj"));
    m_object->setTexture(AssetLoader::loadImage("Assets\\Textures\\quads.jpg"));

    m_light = std::make_shared<core::PointLight>(core::Vec3(0, 10, 0),
                                                 core::Vec3(0.1f, 0.1f, 0.1f));
    m_light->toggleVisibility(true);
}