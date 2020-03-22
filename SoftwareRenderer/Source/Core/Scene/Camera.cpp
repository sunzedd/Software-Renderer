#include "Camera.h"

namespace core
{
Camera::Camera(const Vec3& position)
{
	m_transform.position = position;
	m_transform.forward = Vec3(0, 0, -1);
	m_transform.up = Vec3(0, 1, 0);

	m_viewMatrix = Mat4::lookAt(m_transform.position, 
									Vec3(0, 0, -1),
									Vec3(0, 0, 1));
}

Camera::Camera(const Vec3& position, float fovy, float aspectRatio, float zNear, float zFar)
{
	m_viewFrustum.fovy = fovy;
	m_viewFrustum.aspectRatio = aspectRatio;
	m_viewFrustum.zNear = zNear;
	m_viewFrustum.zFar = zFar;

	m_viewMatrix = Mat4::lookAt(m_transform.position,
									Vec3(0, 0, -1),
									Vec3(0, 0, 1));
}

void Camera::update(unsigned int deltaTime)
{
	/*
	float dRot = dtime * 0.035;
	float dMove = dtime * 0.003;
	float dCamMove = m_cameraSpeed * dtime;

	auto& camera = m_scene->getCamera();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) camera.move(Direction::Left, dCamMove);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) camera.move(Direction::Right, dCamMove);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) camera.move(Direction::Forward, dCamMove);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) camera.move(Direction::Backward, dCamMove);

	//mouse movement
	static bool isMouseRightBtnPressed = false;
	static vec2i lastMouseCursorPosition = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && !isMouseRightBtnPressed)
	{
		isMouseRightBtnPressed = true;
		lastMouseCursorPosition = { sf::Mouse::getPosition().x, sf::Mouse::getPosition().y };
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Right) && isMouseRightBtnPressed)
	{
		isMouseRightBtnPressed = false;
	}

	if (isMouseRightBtnPressed)
	{
		vec2i currentMouseCursorPosition = {
			sf::Mouse::getPosition().x,
			sf::Mouse::getPosition().y
		};

		camera.rotate(Vec2(
			lastMouseCursorPosition.x - currentMouseCursorPosition.x,
			lastMouseCursorPosition.y - currentMouseCursorPosition.y));

		lastMouseCursorPosition = currentMouseCursorPosition;
	}
	*/
}

const Vec3& Camera::getPosition() const
{
	return m_transform.position;
}

void Camera::setPosition(const Vec3& position)
{
	m_transform.position = position;
}

const Mat4& Camera::getViewMatrix()
{
	if (m_isTransformed)
	{
		//TODO: recalc view matrix.
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
}