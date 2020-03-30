#pragma once
#include "../Core/Engine.h"
#include "../Core/Scene/PointLight.h"

#include "Shaders/TextureShader.h"

class Game : public core::App
{
public: 
	Game();
	~Game();

private:
	void update(unsigned int deltaTime) override;
	void render() override;

	void initScene();

private:
	core::DrawableGameObject* m_object;
	std::shared_ptr<core::PointLight> m_light;
	core::Camera* m_camera;
};