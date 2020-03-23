#pragma once
#include <SFML/Graphics.hpp>

#include "../Math/Mat4.h"
#include "../Math/Vec3.h"

#include "CameraBase.h"


#define CORE_CAMERA_VIEWFRUSTUM_FOVY  50.0f
#define CORE_CAMERA_VIEWFRUSTUM_AR    1.3333f
#define CORE_CAMERA_VIEWFRUSTUM_ZNEAR 0.0001f
#define CORE_CAMERA_VIEWFRUSTUM_ZFAR  1000.0f

#define CORE_CAMERA_MOVEMENT_SPEED    0.05f
#define CORE_CAMERA_MOUSE_SENS        0.10f

namespace core
{

enum class Direction
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};

class Camera : public CameraBase
{
    struct _ViewFrustum
    {
        float fovy        = CORE_CAMERA_VIEWFRUSTUM_FOVY;
        float aspectRatio = CORE_CAMERA_VIEWFRUSTUM_AR;
        float zNear       = CORE_CAMERA_VIEWFRUSTUM_ZNEAR;
        float zFar        = CORE_CAMERA_VIEWFRUSTUM_ZFAR;
    };

    struct _Transform
    {
        Vec3 position;
        Vec3 front;
        Vec3 up;
        Vec3 right;

        float yaw;
        float pitch;
    };

public:
    Camera(const Vec3& position = { 0, 0, 0 });
    Camera(const Vec3& position,
           const Vec3& front = { 0, 0, -1 },
           const Vec3& up = { 0, 1, 0 });

    virtual void update(unsigned int deltaTime) override;

    const Vec3& getPosition() const;
    float getMovementSpeed() const;
    
    void move(Direction direction, float delta);

    void setPosition(const Vec3& position);
    void setMovementSpeed(float speed);
    void setMouseSensitivity(float sensitivity);
    void setViewFrustum(float fovy, float aspectRatio, float zNear, float zFar);

    const Mat4& getViewMatrix() override;
    const Mat4& getProjMatrix() override;

private:
    void handleMouse();
    void handleKeyboard(float deltaMove);

protected:
    _Transform m_transform;
    _ViewFrustum m_viewFrustum;

    Mat4 m_viewMatrix;
    Mat4 m_projMatrix;

    bool m_hasProjMatrixModified = true;

    float m_movementSpeed    = CORE_CAMERA_MOVEMENT_SPEED;
    float m_mouseSensitivity = CORE_CAMERA_MOUSE_SENS;
};

}