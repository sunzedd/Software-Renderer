#pragma once
#include "../Core/Engine.h"

class Game : public core::App
{
public: 
	Game();

private:
	void update(unsigned int deltaTime) override;
	void render() override;

	void loadAssets();
	void initScene();

private:
	std::unique_ptr<core::Scene> m_scene;
};