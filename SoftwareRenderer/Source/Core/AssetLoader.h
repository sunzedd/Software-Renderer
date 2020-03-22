#pragma once
#include <iostream>
#include <SFML/Graphics/Image.hpp>

#include "Graphics/Mesh.h"
#include "Exceptions.h"

#define _CRT_SECURE_NO_WARNINGS

namespace Core {

class AssetLoader
{
public:
	static std::shared_ptr<Mesh> loadMesh(const std::string& filepath);
	static std::shared_ptr<sf::Image> loadImage(const std::string& filepath);
};

} // namespace Core