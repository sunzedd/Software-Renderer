#include "Camera.h"

namespace core
{
Camera::Camera(const Vec3& position)
{
    m_transform.position = position;
    m_transform.front = Vec3::forward();
    m_transform.up = Vec3::up();
    m_transform.right = Vec3::right();

    m_transform.yaw = -90.0f;
    m_transform.pitch = 0.0f;

    m_viewMatrix = Mat4::lookAt(m_transform.position, 
                                m_transform.front,
                                m_transform.up);
}

Camera::Camera(const Vec3& position, const Vec3& forward, const Vec3& up)
{
    m_transform.position = position;
    m_transform.front = forward;
    m_transform.up = up;
    m_transform.right = Vec3::right();

    m_transform.yaw = -90.0f;
    m_transform.pitch = 0.0f;

    m_viewMatrix = Mat4::lookAt(m_transform.position,
                                m_transform.front,
                                m_transform.up);
}

void Camera::update(unsigned int deltaTime)
{
    const float deltaMove = m_movementSpeed * deltaTime;

    handleKeyboard(deltaMove);
    handleMouse();
}

const Vec3& Camera::getPosition() const
{
    return m_transform.position;
}

float Camera::getMovementSpeed() const
{
    return m_movementSpeed;
}

void Camera::move(Direction direction, float delta)
{
    switch (direction)
    {
    case Direction::FORWARD:
        m_transform.position += m_transform.front * delta;
        break;
    case Direction::BACKWARD:
        m_transform.position -= m_transform.front * delta;
        break;
    case Direction::LEFT:
        m_transform.position -= m_transform.right * delta;
        break;
    case Direction::RIGHT:
        m_transform.position += m_transform.right * delta;
        break;
    case Direction::UP:
        m_transform.position += m_transform.up * delta;
        break;
    case Direction::DOWN:
        m_transform.position -= m_transform.up * delta;
        break;

    default:
        break;
    }

    m_isTransformed = true;
}

void Camera::setPosition(const Vec3& position)
{
    m_transform.position = position;
}

void Camera::setMovementSpeed(float speed)
{
    m_movementSpeed = speed;
}

void Camera::setMouseSensitivity(float sensitivity)
{
    m_mouseSensitivity = sensitivity;
}

void Camera::setViewFrustum(float fovy, float aspectRatio, float zNear, float zFar)
{
    m_viewFrustum.fovy = fovy;
    m_viewFrustum.aspectRatio = aspectRatio;
    m_viewFrustum.zNear = zNear;
    m_viewFrustum.zFar = zFar;

    m_hasProjMatrixModified = true;
}

const Mat4& Camera::getViewMatrix()
{
    if (m_isTransformed)
    {
        m_viewMatrix = Mat4::lookAt(m_transform.position,
                                    m_transform.position + m_transform.front,
                                    m_transform.up);
        m_isTransformed = false;
    }

    return m_viewMatrix;
}

const Mat4& Camera::getProjMatrix()
{
    if (m_hasProjMatrixModified)
    {
        m_projMatrix = Mat4::perspective(m_viewFrustum.fovy,
                                         m_viewFrustum.aspectRatio,
                                         m_viewFrustum.zNear,
                                         m_viewFrustum.zFar);
    }
    return m_projMatrix;
}

void Camera::handleMouse()
{
    //mouse movement
    static bool isMouseRightButtonPressed = false;
    static int lastMousePositionX = sf::Mouse::getPosition().x;
    static int lastMousePositionY = sf::Mouse::getPosition().y;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !isMouseRightButtonPressed)
    {
        isMouseRightButtonPressed = true;
        lastMousePositionX = sf::Mouse::getPosition().x;
        lastMousePositionY = sf::Mouse::getPosition().y;
    }

    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && isMouseRightButtonPressed)
        isMouseRightButtonPressed = false;

    if (isMouseRightButtonPressed)
    {
        int currentMousePositionX = sf::Mouse::getPosition().x;
        int currentMousePositionY = sf::Mouse::getPosition().y;

        float xoffset = (currentMousePositionX - lastMousePositionX) * m_mouseSensitivity;
        float yoffset = (lastMousePositionY - currentMousePositionY) * m_mouseSensitivity;

        m_transform.yaw += xoffset;
        m_transform.pitch += yoffset;

        if (m_transform.pitch > 89.0f) m_transform.pitch = 89.0f;
        if (m_transform.pitch < -89.0f) m_transform.pitch = -89.0f;

        Vec3 front;
        front.x = cos(Math::toRadians(m_transform.yaw)) *
                  cos(Math::toRadians(m_transform.pitch));
        front.y = sin(Math::toRadians(m_transform.pitch));
        front.z = sin(Math::toRadians(m_transform.yaw)) *
                  cos(Math::toRadians(m_transform.pitch));
        m_transform.front = front.normalize();
        m_transform.right = m_transform.front.cross(m_transform.up);

        lastMousePositionX = currentMousePositionX;
        lastMousePositionY = currentMousePositionY;
    }
}

void Camera::handleKeyboard(float deltaMove)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move(Direction::LEFT,     deltaMove);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move(Direction::RIGHT,    deltaMove);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move(Direction::FORWARD,  deltaMove);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move(Direction::BACKWARD, deltaMove);

    m_isTransformed = true;
}
}