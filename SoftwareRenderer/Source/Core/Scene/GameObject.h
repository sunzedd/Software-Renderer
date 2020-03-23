#pragma once
#include "../Math/Vec3.h"
#include "../Math/Mat4.h"
#include "../Graphics/Mesh.h"

#include "Entity.h"

namespace core
{

struct Transform
{
	Vec3 position = { 0.0f, 0.0f, 0.0f };
	Vec3 rotation = { 0.0f, 0.0f, 0.0f };
	Vec3 scale	  = { 1.0f, 1.0f, 1.0f };
};

class GameObject : public Entity
{
	struct _TransformMatrices
	{
		Mat4 translation;
		Mat4 rotation;
		Mat4 scale;
		Mat4 model;
	};

public:
	GameObject();
	GameObject(const Vec3& position,
			   const Vec3& rotation,
		       const Vec3& scale = Vec3(1.0f, 1.0f, 1.0f));

	Transform& getTransform();

	virtual void update(unsigned int deltaTime) = 0;

protected:
	void recalculateModelMatrix();

protected:
	Transform m_transform;
	_TransformMatrices m_transformMatrices;
};

}