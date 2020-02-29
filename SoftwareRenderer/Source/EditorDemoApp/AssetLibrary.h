#pragma once
#include <SFML/Graphics/Image.hpp>
#include "../Core/Graphics/IShaderProgram.h"
#include "Library.h"

namespace Demo
{
	typedef Library<sf::Image> TextureLibrary;
	typedef Library<Core::IShaderProgram> ShaderLibrary;
}