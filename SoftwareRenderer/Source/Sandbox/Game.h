#pragma once
#include "../Core/Engine.h"
#include "Shaders/TextureShader.h"

class Game : public core::App
{
public: 
	Game();
	~Game();

private:
	void update(unsigned int deltaTime) override;
	void render() override;

	void loadAssets();
	void initScene();

private:
	core::DrawableGameObject* m_object;
	core::Camera* m_camera;
};