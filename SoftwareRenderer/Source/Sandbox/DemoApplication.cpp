#include "DemoApplication.h"

using namespace core;
using namespace std;

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    _initScene();

    m_camera.setViewFrustum(45.0, (float)16 / (float)9, 0.001, 100.0);
    m_camera.setMovementSpeed(0.03f);
    m_camera.setPosition(Vec3(0.0f, 3.0f, 10.0f));
    m_camera.update(0);
}

void DemoApplication::_initScene()
{
    // Loading assets:
    // textures
    auto defaultTexture = AssetLoader::loadDefaultImage();
    auto grassTexture   = AssetLoader::loadImage("Assets\\Textures\\grass_01.jpg");
    auto boxTexture     = AssetLoader::loadImage("Assets\\Textures\\box.jpg");
    auto stoneTexture   = AssetLoader::loadImage("Assets\\Textures\\stone_03.jpg");
    auto earthTexture   = AssetLoader::loadImage("Assets\\Textures\\earth.jpg");

    // meshes
    auto defaultMesh    = AssetLoader::loadDefaultMesh();
    auto sphereMesh     = AssetLoader::loadMesh("Assets\\Meshes\\sphere.obj");
    auto groundMesh     = AssetLoader::loadMesh("Assets\\Meshes\\grid.obj");
    auto humanMesh      = AssetLoader::loadMesh("Assets\\Meshes\\human.obj");

    // default shader
    auto defaultShader = make_shared<ShaderProgram::Default>();

    // Objects creation:
    // lighter
    m_lighter = make_shared<Object3D>();
    m_lighter->setShader(defaultShader);
    m_lighter->setMesh(sphereMesh);
    m_lighter->setPosition(Vec3(0.0f, 3.0f, 2.0f));
    m_lighter->setScale(Vec3(0.1f, 0.1f, 0.1f));

    // Wall of boxes
    auto boxes = make_shared<CompositeObject3D>();
    auto boxShader = make_shared<PhongShader>();
    int boxCounter = 0;
    const int side = 2.0f;
    const float offset = 0.025f;
    for (float x = 0; x < 3 * side; x += side + offset) {
        for (float y = 0; y < 3 * side; y += side + offset) {
            boxCounter++;
            auto box = make_shared<Object3D>();
            box->setShader(boxShader);
            box->setPosition(Vec3(x, y, 0.0f));
            box->setTexture(boxTexture);
            std::string name = "box_" + std::to_string(boxCounter);
            boxes->addComponent(name, box);
        }
    }
    boxes->move(Vec3(-1, 1, -3));
    m_objects.push_back(boxes);
    m_shaders.push_back(boxShader);

    // Ground
    auto ground = make_shared<Object3D>();
    auto groundShader = make_shared<PhongShader>();
    ground->setTexture(grassTexture);
    ground->setMesh(groundMesh);
    ground->setShader(groundShader);
    m_objects.push_back(ground);
    m_shaders.push_back(groundShader);

    // humans
    auto human1 = make_shared<Object3D>();
    auto humanShader = make_shared<PhongShader>();
    human1->setMesh(humanMesh);
    human1->setTexture(defaultTexture);
    human1->setShader(humanShader);
    human1->move(Vec3(0, 3.3, 0));
    human1->scale(Vec3(0.5, 0.5, 0.5));
    m_objects.push_back(human1);
    m_shaders.push_back(humanShader);

    auto human2 = make_shared<Object3D>();
    human2->setMesh(humanMesh);
    human2->setTexture(defaultTexture);
    human2->setShader(humanShader);
    human2->setPosition(Vec3(2, 1.6, 1));
    human2->rotate(Vec3(0, 90, 0));
    human2->scale(Vec3(0.5, 0.5, 0.5));
    m_objects.push_back(human2);
    m_shaders.push_back(humanShader);

    // stone cube
    auto stoneCube = make_shared<Object3D>();
    auto stoneCubeShader = make_shared<PhongShader>();
    stoneCube->setTexture(stoneTexture);
    stoneCube->setShader(stoneCubeShader);
    stoneCube->setPosition(Vec3(0, 1, 0));
    stoneCube->scale(Vec3(0.7, 0.7, 0.7));
    m_objects.push_back(stoneCube);
    m_shaders.push_back(stoneCubeShader);

    // earth sphere
    auto earth = make_shared<Object3D>();
    auto earthShader = make_shared<PhongShader>();
    earth->setMesh(sphereMesh);
    earth->setShader(earthShader);
    earth->setTexture(earthTexture);
    earth->setPosition(Vec3(2, 4.5, 1));
    m_objects.push_back(earth);
    m_shaders.push_back(earthShader);
}

void DemoApplication::update(unsigned int deltaTime)
{
    _handleInput(deltaTime);
    _executeLogicScript(deltaTime);

    // update shader 'uniforms'.
    for (auto& shader : m_shaders)
    {
        auto phongShader = std::dynamic_pointer_cast<PhongShader>(shader);
        phongShader->pointLightSourcePosition = m_lighter->getPosition();
    }

    // update objects state.
    for (auto& object : m_objects)
    {
        if (object->isActive())
            object->update(deltaTime);
    }

    // update camera and light source state.
    m_lighter->update(deltaTime);
    m_camera.update(deltaTime);
}

void DemoApplication::render()
{
    RenderPipeline::instance().beginFrame();

    for (auto& object : m_objects)
    {
        if (object->isVisible())
            object->render(m_camera);
    }

    m_lighter->render(m_camera);
}

void DemoApplication::_handleInput(unsigned int deltaTime)
{
    const float speed = deltaTime * 0.005;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        m_lighter->move(-core::Vec3::right() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        m_lighter->move(core::Vec3::right() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        m_lighter->move(core::Vec3::up() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        m_lighter->move(-core::Vec3::up() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
        m_lighter->move(core::Vec3::forward() * speed);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Dash))
        m_lighter->move(-core::Vec3::forward() * speed);
}

void DemoApplication::_executeLogicScript(unsigned int deltaTime)
{
    // TODO: Create scene class based on hashmap for better object search.
    
    // rotate stone cube
    const float stoneCube_RotationDelta = deltaTime * 0.05;
    auto& stoneCube = m_objects[4];
    stoneCube->rotate(Vec3(0, 1, 0) * stoneCube_RotationDelta);

    // rotate earth sphere
    const float earth_RotationDelta = deltaTime * 0.01;
    auto& earth = m_objects[5];
    earth->rotate(Vec3(1, 1, 1) * earth_RotationDelta);

    // cycle movement of light source
    static const int lighter_MinY = 0.5;
    static const int lighter_MaxY = 5.0;
    static const float lighter_MovementSpeed = 0.001;
    const float lighter_MovementDelta = lighter_MovementSpeed * deltaTime;

    static Vec3 lighter_Direction = Vec3::up();
    if (m_lighter->getPosition().y >= lighter_MaxY && lighter_Direction == Vec3::up())
    {
        lighter_Direction = -Vec3::up();
    }
    if (m_lighter->getPosition().y <= lighter_MinY && lighter_Direction == -Vec3::up())
    {
        lighter_Direction = Vec3::up();
    }

    const Vec3 lighter_Velocity = lighter_Direction * lighter_MovementDelta;
    m_lighter->move(lighter_Velocity);
}