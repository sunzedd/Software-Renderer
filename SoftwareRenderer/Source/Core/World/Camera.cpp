#include "Camera.h"

namespace Core
{
	Camera::Camera(const Vec3& pos /*= Vec3(0, 0, 0)*/)
		:
		ICamera(pos),
		m_fov(45.0f),
		m_zNear(0.001f),
		m_zFar(100.0f),
		m_aspectRatio(4.0f / 3.0f),
		m_viewMatrix(Mat4::translation(-pos)),
		m_projMatrix(Mat4::perspective(m_fov, m_aspectRatio, m_zNear, m_zFar))
	{
		m_isTransformed = true;
	}

	void Camera::setup(float fov, float zNear, float zFar, float aspectRatio)
	{
		m_fov = fov;
		m_zNear = zNear;
		m_zFar = zFar;
		m_aspectRatio = aspectRatio;

		m_projMatrix = Mat4::perspective(m_fov, m_aspectRatio, m_zNear, m_zFar);
		m_isTransformed = true;
	}

	void Camera::move(Direction dir, float delta)
	{
		switch (dir)
		{
		case Core::Direction::Forward:
			m_pos += Vec4(0, 0, -1, 0) * !m_orientation * delta;
			break;
		case Core::Direction::Backward:
			m_pos += Vec4(0, 0, 1, 0) * !m_orientation * delta;
			break;
		case Core::Direction::Left:
			m_pos += Vec4(-1, 0, 0, 0) * !m_orientation * delta;
			break;
		case Core::Direction::Right:
			m_pos += Vec4(1, 0, 0, 0) * !m_orientation * delta;
			break;
		default:
			break;
		}

		m_isTransformed = true;
	}


	void Camera::update(unsigned int dtime)
	{
		if (m_isTransformed)
		{
			const Vec3 invPos = -m_pos;
			m_viewMatrix = Mat4::translation(invPos) * m_orientation;
			m_viewProjMatrix = m_viewMatrix * m_projMatrix;
			m_isTransformed = false;
		}
	}

	void Camera::rotate(const Vec2& delta)
	{
		const Mat4 rot = Mat4::rotationX(delta.y * m_rotVelocity) * Mat4::rotationY(delta.x * m_rotVelocity);

		m_orientation *= rot;
		m_isTransformed = true;
	}
}