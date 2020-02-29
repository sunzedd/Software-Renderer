#pragma once
#include <iostream>

#include "Graphics/Mesh.h"
#include "App.h"

#define _CRT_SECURE_NO_WARNINGS

namespace Core
{
	class AssetLoader
	{
	public:
		class Exception : public App::Exception
		{
		public:
			Exception(const std::string& msg)
				:
				App::Exception(msg) { }
		};

		static std::shared_ptr<Mesh> loadMesh(const std::string& filepath);
		static std::shared_ptr<sf::Image> loadImage(const std::string& filepath);
	};
}