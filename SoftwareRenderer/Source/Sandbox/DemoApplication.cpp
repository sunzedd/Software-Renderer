#include "DemoApplication.h"

using namespace core;
using namespace std;

DemoApplication::DemoApplication()
    :
    App(DEMO_WIDTH, DEMO_HEIGHT, "Demo", false)
{
    createScene();
    initCamera();
}

void DemoApplication::update(unsigned int deltaTime)
{
    // update shaders 'uniforms'.
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
    Renderer::getRendererInstance()->beginFrame();

    for (auto& object : m_objects) 
    {
        if (object->isVisible() && object->isActive())
            object->render(m_camera);
    }

    m_lighter->render(m_camera);
}

void DemoApplication::createScene()
{
    // ***************************** Loading assets *******************************
    auto defaultTexture = AssetLoader::loadDefaultImage();
    auto grassTexture = AssetLoader::loadImage("Assets\\Textures\\quads.jpg");
    auto boxTexture = AssetLoader::loadImage("Assets\\Textures\\box.jpg");
    auto stoneTexture = AssetLoader::loadImage("Assets\\Textures\\stone_03.jpg");
    auto earthTexture = AssetLoader::loadImage("Assets\\Textures\\earth.jpg");

    auto defaultMesh = AssetLoader::loadDefaultMesh();
    auto sphereMesh = AssetLoader::loadMesh("Assets\\Meshes\\sphere.obj");
    auto groundMesh = AssetLoader::loadMesh("Assets\\Meshes\\grid.obj");
    auto humanMesh = AssetLoader::loadMesh("Assets\\Meshes\\human.obj");

    // default shader
    auto defaultShader = make_shared<Shader::Default>();

    // ********************************* Objects creation *************************
    // Light source (SCRIPTED)
    m_lighter = make_shared<Object3D>();
    Script* lighterScript = new LigthSourceScript();
    m_lighter->setAttributes(defaultShader, sphereMesh);
    m_lighter->attachScript(lighterScript);

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
    ground->setAttributes(groundShader, groundMesh, grassTexture);
    m_objects.push_back(ground);
    m_shaders.push_back(groundShader);

    // humans
    auto human1 = make_shared<Object3D>();
    auto humanShader = make_shared<PhongShader>();
    human1->setAttributes(humanShader, humanMesh, defaultTexture);
    human1->move(Vec3(0, 3.3, 0));
    human1->scale(Vec3(0.5, 0.5, 0.5));
    m_objects.push_back(human1);
    m_shaders.push_back(humanShader);

    auto human2 = make_shared<Object3D>();
    human2->setAttributes(humanShader, humanMesh, defaultTexture);
    human2->setPosition(Vec3(2, 1.6, 1));
    human2->rotate(Vec3(0, 90, 0));
    human2->scale(Vec3(0.5, 0.5, 0.5));
    m_objects.push_back(human2);
    m_shaders.push_back(humanShader);

    // stone cube (SCRIPTED)
    auto stoneCube = make_shared<Object3D>();
    auto stoneCubeShader = make_shared<PhongShader>();
    Script* stoneCubeScript = new CubeScript();
    stoneCube->setTexture(stoneTexture);
    stoneCube->setShader(stoneCubeShader);
    stoneCube->attachScript(stoneCubeScript);
    m_objects.push_back(stoneCube);
    m_shaders.push_back(stoneCubeShader);

    // earth sphere (SCRIPTED)
    auto earth = make_shared<Object3D>();
    auto earthShader = make_shared<PhongShader>();
    Script* earthScript = new EarthScript();
    earth->setAttributes(earthShader, sphereMesh, earthTexture);
    earth->attachScript(earthScript);
    m_objects.push_back(earth);
    m_shaders.push_back(earthShader);
}

void DemoApplication::initCamera()
{
    m_camera.setViewFrustum(45.0, (float)16 / (float)9, 0.001, 50.0);
    m_camera.setMovementSpeed(0.03f);
    m_camera.setPosition(Vec3(0.0f, 3.0f, 10.0f));
    m_camera.update(0);
}
