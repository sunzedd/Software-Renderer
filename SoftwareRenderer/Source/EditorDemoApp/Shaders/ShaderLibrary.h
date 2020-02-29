#pragma once
#include <memory>
#include <unordered_map>
#include "../../Core/Graphics/IShaderProgram.h"

namespace Demo
{
	class ShaderLibrary final
	{
	public:
		static ShaderLibrary& instance();

		void add(const std::string& name, std::shared_ptr<Core::IShaderProgram> shader);
		std::shared_ptr<Core::IShaderProgram> get(const std::string& name);

	private:
		ShaderLibrary() { }
		~ShaderLibrary();

	private:
		std::unordered_map<std::string, std::shared_ptr<Core::IShaderProgram>> m_shaders;
		static ShaderLibrary* m_instance;
	};
}