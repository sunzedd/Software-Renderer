#include "DemoApplication.h"

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    _initScene();

    m_camera.setMovementSpeed(0.03f);
}

void DemoApplication::update(unsigned int deltaTime)
{
    _updateSceneLogic(deltaTime);

    m_lighter->update(deltaTime);
    m_camera.update(deltaTime);

    for (auto& object : m_objects)
    {
        object.second->update(deltaTime);

        auto shader = std::dynamic_pointer_cast<PhongShader>(object.second->getShader());
        shader->pointLightSourcePosition = m_lighter->getTransform().getPosition();
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
    objectBuilder.setPosition(0, 5, 0);
    objectBuilder.setScale(0.1f, 0.1f, 0.1f);
    auto lighterObject = objectBuilder.getResult();

    // sphere
    objectBuilder.reset();
    objectBuilder.setPosition(0, 0, -1);
    objectBuilder.setShader(std::make_shared<PhongShader>());
    objectBuilder.setMesh("assets\\Meshes\\sphere.obj");
    auto sphereObject = objectBuilder.getResult();

    // walls
    objectBuilder.reset();
    objectBuilder.setPosition(-4, 3, 0);
    objectBuilder.setRotation(90, 90, 0);
    objectBuilder.setMesh(core::AssetLoader::loadMesh("assets\\Meshes\\grid.obj"));
    objectBuilder.setShader(std::make_shared<PhongShader>());
    objectBuilder.setTexture(core::AssetLoader::loadImage("assets\\Textures\\stone_03.jpg"));
    auto wallObject1 = objectBuilder.getResult();


    // boxes
    auto boxesGroup = std::make_shared<core::Group3D>();
    boxesGroup->setShader(std::make_shared<PhongShader>());
    boxesGroup->setTexture(core::AssetLoader::loadImage("assets\\Textures\\box.jpg"));
    for (int xPos = -3; xPos < 3; xPos += 2)
    {
        for (int yPos = 0; yPos < 3; yPos += 2)
        {
            objectBuilder.reset();
            objectBuilder.setPosition(xPos, yPos, 3);
            auto cubeObject = objectBuilder.getResult();
            boxesGroup->addChild(cubeObject);
        }
    }

    // floor
    objectBuilder.reset();
    objectBuilder.setPosition(0, -1, 0);
    objectBuilder.setMesh(core::AssetLoader::loadMesh("assets\\Meshes\\grid.obj"));
    objectBuilder.setShader(std::make_shared<PhongShader>());
    objectBuilder.setTexture(core::AssetLoader::loadImage("assets\\Textures\\grass_01.jpg"));
    auto floorObject = objectBuilder.getResult();

    m_lighter = lighterObject;
    m_objects.insert(std::make_pair("sphere", std::move(sphereObject)));
    m_objects.insert(std::make_pair("boxes", std::move(boxesGroup)));
    m_objects.insert(std::make_pair("floor", std::move(floorObject)));
    m_objects.insert(std::make_pair("wall_01", std::move(wallObject1)));
}

void DemoApplication::_updateSceneLogic(unsigned int deltaTime)
{
    const float speed = deltaTime * 0.005;

    //m_objects.find("cube")->second->getTransform().rotate(core::Vec3(1, 1, 1) * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_lighter->getTransform().move(-core::Vec3::right() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_lighter->getTransform().move(core::Vec3::right() * speed);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_lighter->getTransform().move(core::Vec3::up() * speed);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_lighter->getTransform().move(-core::Vec3::up() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        m_lighter->getTransform().move(core::Vec3::forward() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
        m_lighter->getTransform().move(-core::Vec3::forward() * speed);
}