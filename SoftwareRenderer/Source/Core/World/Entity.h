#pragma once
#include "WorldObject.h"
#include "../Graphics/Mesh.h"

namespace Core {

class Entity : public WorldObject
{
public:
	Entity(std::shared_ptr<Mesh> mesh, std::shared_ptr<IShaderProgram> shader);
	virtual ~Entity() { } 

	virtual void render(RenderPipeline& renderer);

	const Vec3& getRotation() const { return m_rot; }
	const Vec3& getScale() const { return m_scale; }
	IShaderProgram& getShader() { return *m_pShader; }
	const IShaderProgram& getShader() const { return *m_pShader; }

	void setActivity(bool enabled);
	void setRotation(const Vec3& rot);
	void setScale(const Vec3& scale);
	void setMesh(std::shared_ptr<Mesh> mesh);
	void setShader(std::shared_ptr<IShaderProgram> shader);

	void rotate(const Vec3& delta);
	void scale(const Vec3& scaleFactor);

	virtual void update(unsigned int dtime) override;

protected:
	void recalcModelMatrix();

protected:
	const std::pair<std::string, int> m_id;

	std::shared_ptr<Mesh> m_pMesh;
	std::shared_ptr<IShaderProgram> m_pShader;

	Vec3 m_rot;
	Vec3 m_scale;
	Mat4 m_modelMatrix;

	bool m_isActive;
};

} // namespace Core