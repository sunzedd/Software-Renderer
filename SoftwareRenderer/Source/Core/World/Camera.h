#pragma once
#include "ICamera.h"

namespace Core {

enum class Direction
{
	Forward, Backward,
	Left, Right,
	Up, Down
};

class Camera : public ICamera
{
public:
	Camera(const Vec3& pos = Vec3(0, 0, 0));

	const Mat4& getCameraMatrix() const override { return m_viewProjMatrix; }

	const Mat4& getViewMatrix() const { return m_viewMatrix; }
	const Mat4& getProjMatrix() const { return m_projMatrix; }
	
	void setup(float fov, float zNear, float zFar, float aspectRatio);
	void update(unsigned int dtime) override;

	void rotate(const Vec2& delta);
	void move(Direction dir, float delta);

protected:
	float m_fov;
	float m_zNear;
	float m_zFar;
	float m_aspectRatio;

	Mat4 m_orientation;

	Mat4 m_viewMatrix;
	Mat4 m_projMatrix;
	Mat4 m_viewProjMatrix;

	float m_rotVelocity = 0.3f;
};

} // namespace Core